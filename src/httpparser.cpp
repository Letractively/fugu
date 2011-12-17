#include "http_parser/http_parser.h"
#include "httpparser.h"
#include "query.h"
#include <fstream>
#include <sstream>
#include <boost/regex.hpp>

namespace fugu {

const char	REQ_HEADER_COOKIE_NAME[]	= "Cookie";
const char	COOKIE_SESSION_HASH[]		= "FUGU_SESSION_HASH";
const char	COOKIE_USER_HASH[]			= "FUGU_USER_HASH";

QueryType GetQueryType(http_parser* parse);

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

void HttpParser::ParseCookieHeader(const char *ptr, const size_t len)
{
	boost::regex expression("(\w+)=([^;]*)");

	/*
	boost::tregex_iterator begin(fulls.GetString(),fulls.GetString()+fulls.GetLength(),re), end;
	CString sub;
	for (;begin!=end;++begin){
		boost::tmatch const &what = *begin;
		sub=CString(what[0].first,what[0].length());
		if (sub!="")  //to avoid the empty results
		AfxMessageBox(sub);
	}
	*/

	/*
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
						//TODO: _request->AddCookie(cookie_name, cookie_value);
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
						//TODO: _request->AddCookie(cookie_name, cookie_value);
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
						//TODO: _request->AddCookie(cookie_name, cookie_value);
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
	if (! IsCookieAttribute(cookie_name)){
		//TODO: _request->AddCookie(cookie_name, cookie_value);
	}
	*/
}

int HttpParser::OnRequestUrl(http_parser *parser, const char *buf, size_t len)
{
	HttpParser* p = reinterpret_cast<HttpParser*>(parser->data);
	p->_query->SetUrl(buf, len);

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

bool HttpParser::UrlDecode(const std::string& in, std::string& out)
{
	out.clear();
	out.reserve(in.size());
	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (in[i] == '%')
		{
			if (i + 3 <= in.size())
			{
				int value = 0;
				std::istringstream is(in.substr(i + 1, 2));
				if (is >> std::hex >> value)
				{
					out += static_cast<char>(value);
					i += 2;
				}
				else return false;
			}
			else return false;
		}
		else if (in[i] == '+') out += ' ';
		else out += in[i];
	}
	return true;
}

QueryType GetQueryType(http_parser* parser)
{
	if(parser->upgrade)
		return QueryType::QUERY_WEBSOCKET;

	switch(parser->method)
	{
		case http_method::HTTP_DELETE:
			return QueryType::QUERY_DELETE;
			break;
		case http_method::HTTP_GET:
			return QueryType::QUERY_GET;
			break;
		case http_method::HTTP_POST:
			return QueryType::QUERY_POST;
			break;
		case http_method::HTTP_PUT:
			return QueryType::QUERY_PUT;
			break;
		default:
			return QueryType::NOT_SUPPORTED;
			break;
	}
}

int HttpParser::OnBody(http_parser *parser, const char *buf, size_t len) { return 0; }
int HttpParser::OnMessageBegin(http_parser *parser) { return 0; }
int HttpParser::MessageCompleted(http_parser *parser) { return 0; }
int HttpParser::HeadersCompleted(http_parser *parser) { return 0; }

}