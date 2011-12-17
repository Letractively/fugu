#include "jsonreply.h"

namespace fugu {

JsonReply::JsonReply()
	:_stream(&_streambuf)
	,_blockedError(false)
	,_hasChanges(false)
{
}

JsonReply::~JsonReply()
{
}

void JsonReply::SetError(const std::string& error, bool blocked)
{
	_hasChanges = true;
	_error = error;
	_blockedError = blocked;
}

bool JsonReply::HadError() const
{
	return _error.empty() || _blockedError;
}

bool JsonReply::BlockedError() const
{
	return _blockedError;
}

void JsonReply::SetJS(const std::string& id, const std::string& js)
{
	_hasChanges = true;
	_jsId = id;
	_jsCode = js;
}

void JsonReply::SetHtml(const std::string& region, const std::string& html)
{
	_hasChanges = true;
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
//	"JS": {"id": "scriptid_1", "js script"}
//}
	if(_hasChanges)
	{
		_stream << "{ \"Error\": { \"Blocked\":";

		if(_blockedError)
			_stream << TRUE_JSON_VALUE;
		else
			_stream << FALSE_JSON_VALUE;

		_stream	<< ", \"Message\":\"" << _error << "\"}";

		if(!_htmlRegion.empty() && !_htmlContent.empty())
			_stream	<< ", \"Html\": {\"Region\": " << _htmlRegion << "\" \"Content\": \"" << _htmlContent << "\" }";

		if(!_jsId.empty() && !_jsCode.empty())
				_stream << ", \"JS\": {\"" << _jsId << "\", \"Script\": \"" << _jsCode << "\" }";

		_stream	<< "}";
	}

	return _streambuf;
}

}