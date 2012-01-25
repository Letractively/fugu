#include "jsonreply.h"

namespace fugu {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseJsonReply::BaseJsonReply()
	:Reply(HTTP_REPLY)
	,_blockedError(false)
{
}

BaseJsonReply::~BaseJsonReply()
{
}

void BaseJsonReply::SetError(const std::string& error, bool blocked)
{
	_error = error;
	_blockedError = blocked;
}

bool BaseJsonReply::HasError() const
{
	return _error.empty() || _blockedError;
}

bool BaseJsonReply::BlockedError() const
{
	return _blockedError;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
JsonReply::JsonReply()
	:_stream(&_streambuf)
{
}

JsonReply::JsonReply(StringPtr json)
	:_stream(&_streambuf)
	,_json(json)
{
}

JsonReply::~JsonReply()
{
}

void JsonReply::SetJS(const std::string& id, const std::string& js)
{
	_jsId = id;
	_jsCode = js;
}

void JsonReply::SetJson(StringPtr json)
{
	_json = json;
}

void JsonReply::SetHtml(const std::string& region, const std::string& html)
{
	_htmlRegion = region;
	_htmlContent = html;
}

bool JsonReply::Streamed() const
{
	return true;
}

boost::asio::streambuf& JsonReply::ResponseStream() const
{

static std::string TRUE_JSON_VALUE = "\"true\"";
static std::string FALSE_JSON_VALUE = "\"false\"";

//{
//	"Error":
//	{
//		"Blocked": "true/false",
//		"Message": "string"
//	},
//	"Html": { "region": "center", "content" : "content html" },
//	"Json": { any data },
//	"JS": {"id": "scriptid_1", "js script"}
//}

	_stream << "{ \"Error\": { \"Blocked\":";

	if(_blockedError)
		_stream << TRUE_JSON_VALUE;
	else
		_stream << FALSE_JSON_VALUE;

	_stream	<< ", \"Message\":\"" << _error << "\"}";

	if(!_htmlRegion.empty() && !_htmlContent.empty())
		_stream	<< ", \"Html\": {\"Region\": " << _htmlRegion << "\" \"Content\": \"" << _htmlContent << "\" }";

	if(_json && !_json->empty()) {
		// TODO: check for {}
		_stream << ", \"Json\":" << *_json;
	}

	if(!_jsId.empty() && !_jsCode.empty())
		_stream << ", \"JS\": {\"" << _jsId << "\", \"Script\": \"" << _jsCode << "\" }";

	_stream	<< "}";

	size_t contentSize = _streambuf.size();
	_stream.seekp(0);

	_stream << "HTTP/1.1 200 OK\r\nContent-Type: json\r\nContent-Length: "
			<< contentSize << "\r\n";

	StringPtr headers = Reply::Headers();
	if(headers && !headers->empty())
		_stream << *headers;

	_stream << "\r\n";

	return _streambuf;
}

}