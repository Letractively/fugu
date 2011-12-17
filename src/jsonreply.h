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
//	"Html": { "region": "center", "content" : "content html" },
//	"JS": {"id": "scriptid_1", "js script"}
//}

class JsonReply : public Reply,  private boost::noncopyable
{
public:
	JsonReply();
	virtual ~JsonReply();

	bool HadError() const;
	bool BlockedError() const;
	void SetError(const std::string& error, bool blocked = false);
	void SetJS(const std::string& id, const std::string& js);
	void SetHtml(const std::string& region, const std::string& html);
	bool Streamed() const;
	boost::asio::streambuf& ResponseStream() const;

protected:
	bool _hasChanges;
	bool _blockedError;
	std::string _error;
	std::string _jsId;
	std::string _jsCode;
	std::string _htmlRegion;
	std::string _htmlContent;
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