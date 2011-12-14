#ifndef __FUGU_HTTP_PARSER__
#define __FUGU_HTTP_PARSER__

#include <iostream>
#include "prerequisites.h"

struct http_parser;
enum http_method;

namespace fugu {

enum HttpMethods;
class HttpParser : private boost::noncopyable
{
public:
	HttpParser();
	~HttpParser();
	bool ParseRequest(HttpRequestPtr request, const char *data, std::size_t len);
	void ParseCookieHeader(const char *ptr, const size_t len);

	static int OnRequestUrl(http_parser *parser, const char *buf, size_t len);
	static int OnHeaderField (http_parser *parser, const char *buf, size_t len);
	static int OnHeaderValue(http_parser *parser, const char *buf, size_t len);
	static int OnBody (http_parser *parser, const char *buf, size_t len);
	static int OnCountBody(http_parser *parser, const char *buf, size_t len);
	static int OnMessageBegin(http_parser *parser);
	static int HeadersCompleted(http_parser *parser);
	static int MessageCompleted(http_parser *parser);

	static HttpMethods ConvertHttpMethod(http_method method);
	static bool UrlDecode(const std::string& in, std::string& out);

private:
	HttpRequestPtr _request;
	char _headerName[100];
	size_t _headerNameLen;
	bool _cookieField;
};

}

#endif