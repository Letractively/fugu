#include "httpparseradapter.h"
#include "http_parser.h"
#include "httprequest.h"

namespace fugu {

const char			REQ_HEADER_COOKIE_NAME[]	= "Cookie";
const unsigned int	COOKIE_VALUE_MAX		= 1024 * 1024;	// 1 MB
const unsigned int	COOKIE_NAME_MAX			= 1024;	// 1 KB

int OnRequestUrl (http_parser *parser, const char *buf, size_t len);
int OnHeaderField (http_parser *parser, const char *buf, size_t len);
int OnHeaderValue (http_parser *parser, const char *buf, size_t len);
int OnBody (http_parser *parser, const char *buf, size_t len);
int OnCountBody (http_parser *parser, const char *buf, size_t len);
int OnMessageBegin (http_parser *parser);
int HeadersCompleted (http_parser *parser);
int MessageCompleted (http_parser *parser);
HTTPMethods ConvertHttpMethod(http_method method);

HttpParserAdapter::HttpParserAdapter()
	:HeaderNameLen(0)
	,CookieField(false)
{
}

HttpParserAdapter::~HttpParserAdapter()
{
}

bool HttpParserAdapter::ParseRequest(HttpRequest* request, const char *data, size_t len)
{
	Request = request;

	http_parser_settings parserSettings;
	parserSettings.on_message_begin = OnMessageBegin;
	parserSettings.on_header_field = OnHeaderField;
	parserSettings.on_header_value = OnHeaderValue;
	parserSettings.on_url = OnRequestUrl;
	parserSettings.on_body = OnCountBody;
	parserSettings.on_headers_complete = HeadersCompleted;
	parserSettings.on_message_complete = MessageCompleted;

	http_parser parser;
	http_parser_init(&parser, HTTP_REQUEST);
	parser.data = this;
	size_t nparsed = http_parser_execute(&parser, &parserSettings, data, len);
	return parser.http_errno == 0;
}

inline bool IsControl(int c)
{
	return( (c >= 0 && c <= 31) || c == 127);
}


inline bool IsCookieAttribute(const std::string& name)
{
	return (name.empty() || name[0] == '$' 
			|| (name=="Comment" || name=="Domain" 
			|| name=="Max-Age" || name=="Path" 
			|| name=="Secure" || name=="Version" || name=="Expires"));
}

void HttpParserAdapter::ParseCookieHeader(const char *ptr, const size_t len)
{

	// The current implementation ignores cookie attributes which begin with '$'
	// (i.e. $Path=/, $Domain=, etc.)

	// used to track what we are parsing
	enum CookieParseState {
		COOKIE_PARSE_NAME, COOKIE_PARSE_VALUE, COOKIE_PARSE_IGNORE
	} parse_state = COOKIE_PARSE_NAME;

	// misc other variables used for parsing
	const char * const end = ptr + len;
	std::string cookie_name;
	std::string cookie_value;
	char value_quote_character = '\0';

	// iterate through each character
	while (ptr < end) {
		switch (parse_state) {

		case COOKIE_PARSE_NAME:
			// parsing cookie name
			if (*ptr == '=') {
				// end of name found (OK if empty)
				value_quote_character = '\0';
				parse_state = COOKIE_PARSE_VALUE;
			} else if (*ptr == ';' || *ptr == ',') {
				// ignore empty cookie names since this may occur naturally
				// when quoted values are encountered
				if (! cookie_name.empty()) {
					// value is empty (OK)
					if (! IsCookieAttribute(cookie_name))
						Request->AddCookie(cookie_name, cookie_value);
					cookie_name.erase();
				}
			} else if (*ptr != ' ') {	// ignore whitespace
				// check if control character detected, or max sized exceeded
				if (IsControl(*ptr) || cookie_name.size() >= COOKIE_NAME_MAX)
					return;
				// character is part of the name
				cookie_name.push_back(*ptr);
			}
			break;

		case COOKIE_PARSE_VALUE:
			// parsing cookie value
			if (value_quote_character == '\0') {
				// value is not (yet) quoted
				if (*ptr == ';' || *ptr == ',') {
					// end of value found (OK if empty)
					if (! IsCookieAttribute(cookie_name))
						Request->AddCookie(cookie_name, cookie_value);
					cookie_name.erase();
					cookie_value.erase();
					parse_state = COOKIE_PARSE_NAME;
				} else if (*ptr == '\'' || *ptr == '"') {
					if (cookie_value.empty()) {
						// begin quoted value
						value_quote_character = *ptr;
					} else if (cookie_value.size() >= COOKIE_VALUE_MAX) {
						// max size exceeded
						return;
					} else {
						// assume character is part of the (unquoted) value
						cookie_value.push_back(*ptr);
					}
				} else if (*ptr != ' ' || !cookie_value.empty()) {	// ignore leading unquoted whitespace
					// check if control character detected, or max sized exceeded
					if (IsControl(*ptr) || cookie_value.size() >= COOKIE_VALUE_MAX)
						return;
					// character is part of the (unquoted) value
					cookie_value.push_back(*ptr);
				}
			} else {
				// value is quoted
				if (*ptr == value_quote_character) {
					// end of value found (OK if empty)
					if (! IsCookieAttribute(cookie_name))
						Request->AddCookie(cookie_name, cookie_value);
					cookie_name.erase();
					cookie_value.erase();
					parse_state = COOKIE_PARSE_IGNORE;
				} else if (cookie_value.size() >= COOKIE_VALUE_MAX) {
					// max size exceeded
					return;
				} else {
					// character is part of the (quoted) value
					cookie_value.push_back(*ptr);
				}
			}
			break;

		case COOKIE_PARSE_IGNORE:
			// ignore everything until we reach a comma "," or semicolon ";"
			if (*ptr == ';' || *ptr == ',')
				parse_state = COOKIE_PARSE_NAME;
			break;
		}

		++ptr;
	}

	// handle last cookie in string
	if (! IsCookieAttribute(cookie_name))
		Request->AddCookie(cookie_name, cookie_value);
}

int OnRequestUrl(http_parser *parser, const char *buf, size_t len)
{
	HttpParserAdapter* p = reinterpret_cast<HttpParserAdapter*>(parser->data);
	p->Request->SetUrl(std::string(buf, len));
	return 0;
}

int OnHeaderField (http_parser *parser, const char *buf, size_t len)
{
	HttpParserAdapter* p = reinterpret_cast<HttpParserAdapter*>(parser->data);
	if(memcmp(REQ_HEADER_COOKIE_NAME, buf, len)==0) {
		p->CookieField = true;
	}
	else {
		memcpy(p->HeaderName, buf, len);
		p->HeaderNameLen = len;
	}

	return 0;
}

int OnHeaderValue(http_parser *parser, const char *buf, size_t len)
{
	HttpParserAdapter* p = reinterpret_cast<HttpParserAdapter*>(parser->data);
	if(p->CookieField) {
		p->ParseCookieHeader(buf, len);
	}
	else {
		p->Request->AddHeader(std::string(p->HeaderName,p->HeaderNameLen), std::string(buf,len));
	}
	return 0;
}

int OnBody (http_parser *parser, const char *buf, size_t len)
{
	HttpRequest* request = reinterpret_cast<HttpRequest*>(parser->data);
	return 0;
}

int OnCountBody(http_parser *parser, const char *buf, size_t len)
{
	HttpRequest* adapter = reinterpret_cast<HttpRequest*>(parser->data);
	return 0;
}

int OnMessageBegin(http_parser *parser)
{
	HttpRequest* request = reinterpret_cast<HttpRequest*>(parser->data);
	return 0;
}

int HeadersCompleted(http_parser *parser)
{
	HttpParserAdapter* p = reinterpret_cast<HttpParserAdapter*>(parser->data);
	p->Request->SetContentLength(parser->content_length);
	p->Request->SetMethod(ConvertHttpMethod((http_method)parser->method));
	p->Request->SetMajorVersion(parser->http_major);
	p->Request->SetMinorVersion(parser->http_minor);
	p->Request->SetKeepAlive((bool)http_should_keep_alive(parser));
	return 0;
}

int MessageCompleted(http_parser *parser)
{
	return 0;
}

HTTPMethods ConvertHttpMethod(http_method method)
{
	switch(method)
	{
		case http_method::HTTP_DELETE:
			return HTTPMethods::HTTP_DELETE;
			break;
		case http_method::HTTP_GET:
			return HTTPMethods::HTTP_GET;
			break;
		case http_method::HTTP_POST:
			return HTTPMethods::HTTP_POST;
			break;
		case http_method::HTTP_PUT:
			return HTTPMethods::HTTP_PUT;
			break;
		default:
			return HTTPMethods::NOT_SUPPORTED;
			break;
	}
}

}