#include "http_parser/http_parser.h"
#include "httpparser.h"
#include "query.h"
#include <fstream>
#include <sstream>
#include <boost/regex.hpp>
#include <algorithm>

namespace fugu {

const char	REQ_HEADER_COOKIE_NAME[]		= "Cookie";

const char	COOKIE_SESSION_HASH[]			= "FUGU_SESSION_HASH=";
const int	COOKIE_SESSION_HASH_LEN			= sizeof(COOKIE_SESSION_HASH)-1;

const char	COOKIE_USER_HASH[]				= "FUGU_USER_HASH=";
const int	COOKIE_USER_HASH_LEN			= sizeof(COOKIE_USER_HASH)-1;

const char	FUGU_CONTENT[]					= "FUGU_CONTENT=";
const int	FUGU_CONTENT_LEN				= sizeof(FUGU_CONTENT)-1;

const char	QUERY_STRING_VIEW_NAME[]		= "view=";
const char	QUERY_STRING_VIEW_NAME_HIGH[]	= "VIEW=";
const int QUERY_STRING_VIEW_NAME_LEN		= sizeof(QUERY_STRING_VIEW_NAME)-1;

QueryMethod GetQueryMethod(http_parser* parse);

HttpParser::HttpParser()
	:_headerNameLen(0)
	,_cookieField(false)
{
}

HttpParser::~HttpParser()
{
}

bool HttpParser::ParseRequest(QueryPtr query, const char *data, size_t len)
{
	_query = query;

	http_parser_settings parserSettings;
	parserSettings.on_message_begin = HttpParser::OnMessageBegin;
	parserSettings.on_header_field = HttpParser::OnHeaderField;
	parserSettings.on_header_value = HttpParser::OnHeaderValue;
	parserSettings.on_url = HttpParser::OnRequestUrl;
	parserSettings.on_body = HttpParser::OnCountBody;
	parserSettings.on_headers_complete = HttpParser::HeadersCompleted;
	parserSettings.on_message_complete = HttpParser::MessageCompleted;

	http_parser parser;
	http_parser_init(&parser, HTTP_REQUEST);
	parser.data = this;
	size_t nparsed = http_parser_execute(&parser, &parserSettings, data, len);
	return parser.http_errno == 0;
}

void HttpParser::ParseCookieHeader(const char *ptr, const size_t len)
{
	// Example: "FUGU_CONTENT=viewseditor; FUGU_TEST=viewseditor"

	// misc other variables used for parsing
	const char * const end = ptr + len;
	const char* cookie = ptr;
	
	do
	{
		const char* endvalue = strchr(cookie, ';');
		
		if(!endvalue)
			endvalue = end;
		else if(endvalue > end)
			return;

		if(_query->ViewName().empty() && strncmp(FUGU_CONTENT, cookie, FUGU_CONTENT_LEN) == 0) {
			_query->SetViewName(cookie + FUGU_CONTENT_LEN, endvalue - (cookie + FUGU_CONTENT_LEN));
		}
		else if(strncmp(COOKIE_SESSION_HASH, cookie, COOKIE_SESSION_HASH_LEN) == 0) {
			_query->SetSessionHash(cookie + COOKIE_SESSION_HASH_LEN, endvalue - (cookie + COOKIE_SESSION_HASH_LEN));
		}
		else if(strncmp(COOKIE_USER_HASH, cookie, COOKIE_USER_HASH_LEN) == 0) {
			_query->SetUserHash(cookie + COOKIE_USER_HASH_LEN, endvalue - (cookie + COOKIE_USER_HASH_LEN));
		}

		cookie = strchr(cookie, ' ');

		if(!cookie) return;

		while(isspace(*cookie)) 
			cookie++;
	}
	while(cookie < end);
}



int HttpParser::OnRequestUrl(http_parser *parser, const char *buf, size_t len)
{
	HttpParser* p = reinterpret_cast<HttpParser*>(parser->data);

	const char * const end = buf + len;
	const char* querystring = strchr(buf, '?');

	if(querystring && querystring <  end) {
		p->_query->SetUri(buf, querystring - buf);

		// Skip character '?'
		querystring += 1;

		if(strncmp(QUERY_STRING_VIEW_NAME, querystring, QUERY_STRING_VIEW_NAME_LEN) == 0 
			||strncmp(QUERY_STRING_VIEW_NAME_HIGH, querystring, QUERY_STRING_VIEW_NAME_LEN) == 0 ) 
		{
			p->_query->SetViewName(querystring + QUERY_STRING_VIEW_NAME_LEN, 
									end - (querystring + QUERY_STRING_VIEW_NAME_LEN));
		}
	}
	else {
		p->_query->SetUri(buf, len);
	}

	return 0;
}

int HttpParser::OnHeaderField (http_parser *parser, const char *buf, size_t len)
{
	if(memcmp(REQ_HEADER_COOKIE_NAME, buf, len)==0) {
		HttpParser* p = reinterpret_cast<HttpParser*>(parser->data);
		p->_cookieField = true;
	}

	return 0;
}

int HttpParser::OnHeaderValue(http_parser *parser, const char *buf, size_t len)
{
	HttpParser* p = reinterpret_cast<HttpParser*>(parser->data);

	if(p->_cookieField)
		p->ParseCookieHeader(buf, len);

	p->_cookieField = false;
	return 0;
}

int HttpParser::OnCountBody(http_parser *parser, const char *buf, size_t len)
{
	HttpParser* p = reinterpret_cast<HttpParser*>(parser->data);
	p->_query->SetContent(buf, len);
	return 0;
}

QueryMethod GetQueryMethod(http_parser* parser)
{
	if(parser->upgrade)
		return QueryMethod::QUERY_WEBSOCKET;

	switch(parser->method)
	{
		case http_method::HTTP_DELETE:
			return QueryMethod::QUERY_DELETE;
			break;
		case http_method::HTTP_GET:
			return QueryMethod::QUERY_GET;
			break;
		case http_method::HTTP_POST:
			return QueryMethod::QUERY_POST;
			break;
		case http_method::HTTP_PUT:
			return QueryMethod::QUERY_PUT;
			break;
		default:
			return QueryMethod::NOT_SUPPORTED;
			break;
	}
}

int HttpParser::OnBody(http_parser *parser, const char *buf, size_t len) { return 0; }
int HttpParser::OnMessageBegin(http_parser *parser) { return 0; }
int HttpParser::MessageCompleted(http_parser *parser) { return 0; }
int HttpParser::HeadersCompleted(http_parser *parser) { return 0; }

}