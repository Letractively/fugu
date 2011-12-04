#ifndef __FUGU_HTTP_REQUEST_PARSER__
#define __FUGU_HTTP_REQUEST_PARSER__

#include "httpmessage.h"
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

namespace fugu {



// A request received from a client.
class HttpRequestParser : private boost::noncopyable
{
public:
	HttpRequestParser();
	~HttpRequestParser();

	boost::tribool Parse(HttpRequest& http_msg, boost::system::error_code& ec);

private:

	// state used to keep track of where we are in parsing the HTTP message
	enum MessageParseState {
		PARSE_START, PARSE_HEADERS, PARSE_CONTENT,
		PARSE_CONTENT_NO_LENGTH, PARSE_CHUNKS, PARSE_END
	} _parseState;

	/// state used to keep track of where we are in parsing the HTTP headers
	/// (only used if MessageParseState == PARSE_HEADERS)
	enum HeadersParseState {
		PARSE_METHOD_START, PARSE_METHOD, PARSE_URI_STEM, PARSE_URI_QUERY,
		PARSE_HTTP_VERSION_H, PARSE_HTTP_VERSION_T_1, PARSE_HTTP_VERSION_T_2,
		PARSE_HTTP_VERSION_P, PARSE_HTTP_VERSION_SLASH,
		PARSE_HTTP_VERSION_MAJOR_START, PARSE_HTTP_VERSION_MAJOR,
		PARSE_HTTP_VERSION_MINOR_START, PARSE_HTTP_VERSION_MINOR,
		PARSE_STATUS_CODE_START, PARSE_STATUS_CODE, PARSE_STATUS_MESSAGE,
		PARSE_EXPECTING_NEWLINE, PARSE_EXPECTING_CR,
		PARSE_HEADER_WHITESPACE, PARSE_HEADER_START, PARSE_HEADER_NAME,
		PARSE_SPACE_BEFORE_HEADER_VALUE, PARSE_HEADER_VALUE,
		PARSE_EXPECTING_FINAL_NEWLINE, PARSE_EXPECTING_FINAL_CR
	} _headersParseState;

	/// state used to keep track of where we are in parsing chunked content
	/// (only used if MessageParseState == PARSE_CHUNKS)
	enum ChunkedContentParseState {
		PARSE_CHUNK_SIZE_START, PARSE_CHUNK_SIZE, 
		PARSE_EXPECTING_CR_AFTER_CHUNK_SIZE,
		PARSE_EXPECTING_LF_AFTER_CHUNK_SIZE, PARSE_CHUNK, 
		PARSE_EXPECTING_CR_AFTER_CHUNK, PARSE_EXPECTING_LF_AFTER_CHUNK,
		PARSE_EXPECTING_FINAL_CR_AFTER_LAST_CHUNK, 
		PARSE_EXPECTING_FINAL_LF_AFTER_LAST_CHUNK
	} _chumkedParseState;

};

/*
enum HTTPMethods
{
	GET,
	POST
	PUT,
	DELETE
};

//#include <boost/logic/tribool.hpp>
//#include <boost/tuple/tuple.hpp>

// Parser for incoming requests.
class RequestRarser
{
public:
	/// Construct ready to parse the request method.
	RequestRarser();

	/// Reset to initial parser state.
	void Reset();

	/// Parse some data. The tribool return value is true when a complete request
	/// has been parsed, false if the data is invalid, indeterminate when more
	/// data is required. The InputIterator return value indicates how much of the
	/// input has been Consumed.
	template <typename InputIterator>
	boost::tuple<boost::tribool, InputIterator> Parse(Request& req, InputIterator begin, InputIterator end)
	{
		while (begin != end)
		{
			boost::tribool result = Consume(req, *begin++);
			if (result || !result)
			return boost::make_tuple(result, begin);
		}
		boost::tribool result = boost::indeterminate;
		return boost::make_tuple(result, begin);
	}

private:
	/// Handle the next character of input.
	boost::tribool Consume(Request& req, char input);

	/// Check if a byte is an HTTP character.
	static bool IsChar(int c);

	/// Check if a byte is an HTTP control character.
	static bool IsCtl(int c);

	/// Check if a byte is defined as an HTTP tspecial character.
	static bool IsTspecial(int c);

	/// Check if a byte is a digit.
	static bool IsDigit(int c);

	/// The current state of the parser.
	enum State
	{
		method_start,
		method,
		uri,
		http_version_h,
		http_version_t_1,
		http_version_t_2,
		http_version_p,
		http_version_slash,
		http_version_major_start,
		http_version_major,
		http_version_minor_start,
		http_version_minor,
		expecting_newline_1,
		header_line_start,
		header_lws,
		header_name,
		space_before_header_value,
		header_value,
		expecting_newline_2,
		expecting_newline_3
	} state_;
};
*/

}

#endif