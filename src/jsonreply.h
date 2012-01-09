#ifndef __FUGU_JSON_RESPONSE__
#define __FUGU_JSON_RESPONSE__

#include "prerequisites.h"
#include "reply.h"

namespace fugu {

// Json response with the following  format:
//{
//	"Error":
//	{
//		"Blocked": "true/false",
//		"Message": "string"
//	},
//	"Html": { "Region": "center", "Content" : "content html" },
//	"Json": { any data },
//	"JS": {"Id": "scriptid_1", "js script"}
//}

class BaseJsonReply : public Reply
{
public:
	BaseJsonReply();
	virtual ~BaseJsonReply();

	bool HasError() const;
	bool BlockedError() const;
	void SetError(const std::string& error, bool blocked = false);

protected:
	bool _blockedError;
	std::string _error;
};

class JsonReply : public BaseJsonReply,  private boost::noncopyable
{
public:
	JsonReply();
	JsonReply(StringPtr json);
	virtual ~JsonReply();
	void SetJS(const std::string& id, const std::string& js);
	void SetJson(StringPtr json);
	void SetHtml(const std::string& region, const std::string& html);
	bool Streamed() const;
	boost::asio::streambuf& ResponseStream() const;

protected:
	std::string _jsId;
	std::string _jsCode;
	std::string _htmlRegion;
	std::string _htmlContent;
	StringPtr _json;
	mutable boost::asio::streambuf _streambuf;
	mutable std::ostream _stream;
};

// Json response with the following  format:
//{
//	"Error":
//	{
//		"Blocked": "true/false",
//		"Message": "string"
//	},
//	"Html":
//	[
//		{ "region": "center", "content" : "content html" },
//		{ "region": "top", "content" : "content html" },
//		{ "region": "left", "content" : "content html" }
//	],
//	"JS":
//	[
//		{"id": "scriptid_1", "js script"},
//		...
//		{"id": "scriptid_n", "js script"}
//	]
//}

}

#endif