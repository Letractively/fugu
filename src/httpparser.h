#ifndef __FUGU_HTTP_PARSER__
#define __FUGU_HTTP_PARSER__

#include <iostream>
#include "prerequisites.h"

namespace fugu {

class HttpParser : private boost::noncopyable
{
public:
	HttpParser();
	~HttpParser();
	bool ParseRequest(HttpRequestPtr request, const char *data, std::size_t len);
	void ParseCookieHeader(const char *ptr, const size_t len);

	HttpRequestPtr Request;
	char HeaderName[100];
	size_t HeaderNameLen;
	bool CookieField;
};

}

#endif