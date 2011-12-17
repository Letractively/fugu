#ifndef __FUGU_JSON_RESPONSE__
#define __FUGU_JSON_RESPONSE__

#include "prerequisites.h"
#include <string>
#include <streambuf>
#include <boost/asio.hpp>

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

class JsonReply : private boost::noncopyable
{
public:
	JsonReply();
	virtual ~JsonReply();

	void SetError(const std::string& error, bool blocked = false);
	bool HadError() const;
	bool BlockedError() const;
	void SetJS(const std::string& id, const std::string& js);
	void SetHtml(const std::string& region, const std::string& html);
	boost::asio::streambuf& StreamBuffer();

protected:
	bool _blockedError;
	std::string _error;
	std::string _jsId;
	std::string _jsCode;
	std::string _htmlRegion;
	std::string _htmlContent;
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