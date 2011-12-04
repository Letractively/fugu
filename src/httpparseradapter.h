#ifndef __FUGU_HTTP_PARSER_ADAPTER__
#define __FUGU_HTTP_PARSER_ADAPTER__

#include <iostream>
#include <boost/noncopyable.hpp>

namespace fugu {

class HttpRequest;
class HttpParserAdapter : private boost::noncopyable
{
public:
	HttpParserAdapter();
	~HttpParserAdapter();
	bool ParseRequest(HttpRequest* request, const char *data, std::size_t len);
	void ParseCookieHeader(const char *ptr, const size_t len);

	HttpRequest* Request;
	char HeaderName[100];
	size_t HeaderNameLen;
	bool CookieField;
};

}

#endif