#include "HttpResponse.h"

namespace fugu {

const std::string SET_COOKIE = "Set-Cookie";

void HttpResponse::SetCookie(const std::string& name, const std::string& value)
{
	HttpCookies::iterator iter = _cookies.find(name);
	if(iter == _cookies.end())
		iter->second = value;
	else
		_cookies.insert(std::make_pair<std::string, std::string>(name, value));
}

void HttpResponse::DeleteCookie(const std::string& name)
{
}

/*
const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

std::vector<boost::asio::const_buffer> HttpResponse::ToBuffers()
{
	std::vector<boost::asio::const_buffer> buffers;

	for (std::size_t i = 0; i < _headers.size(); ++i)
	{
		HttpHeader& h = _headers[i];
		buffers.push_back(boost::asio::buffer(h.Name()));
		buffers.push_back(boost::asio::buffer(name_value_separator));
		buffers.push_back(boost::asio::buffer(h.Value()));
		buffers.push_back(boost::asio::buffer(crlf));
	}

	buffers.push_back(boost::asio::buffer(crlf));
	buffers.push_back(boost::asio::buffer(content));

	return buffers;
}
*/

const std::string HttpResponse::HTTP_REASON_CONTINUE                        = "Continue";
const std::string HttpResponse::HTTP_REASON_SWITCHING_PROTOCOLS             = "Switching Protocols";
const std::string HttpResponse::HTTP_REASON_OK                              = "OK";
const std::string HttpResponse::HTTP_REASON_CREATED                         = "Created";
const std::string HttpResponse::HTTP_REASON_ACCEPTED                        = "Accepted";
const std::string HttpResponse::HTTP_REASON_NONAUTHORITATIVE                = "Non-Authoritative Information";
const std::string HttpResponse::HTTP_REASON_NO_CONTENT                      = "No Content";
const std::string HttpResponse::HTTP_REASON_RESET_CONTENT                   = "Reset Content";
const std::string HttpResponse::HTTP_REASON_PARTIAL_CONTENT                 = "Partial Content";
const std::string HttpResponse::HTTP_REASON_MULTIPLE_CHOICES                = "Multiple Choices";
const std::string HttpResponse::HTTP_REASON_MOVED_PERMANENTLY               = "Moved Permanently";
const std::string HttpResponse::HTTP_REASON_FOUND                           = "Found";
const std::string HttpResponse::HTTP_REASON_SEE_OTHER                       = "See Other";
const std::string HttpResponse::HTTP_REASON_NOT_MODIFIED                    = "Not Modified";
const std::string HttpResponse::HTTP_REASON_USEPROXY                        = "Use Proxy";
const std::string HttpResponse::HTTP_REASON_TEMPORARY_REDIRECT              = "Temporary Redirect";
const std::string HttpResponse::HTTP_REASON_BAD_REQUEST                     = "Bad Request";
const std::string HttpResponse::HTTP_REASON_UNAUTHORIZED                    = "Unauthorized";
const std::string HttpResponse::HTTP_REASON_PAYMENT_REQUIRED                = "Payment Required";
const std::string HttpResponse::HTTP_REASON_FORBIDDEN                       = "Forbidden";
const std::string HttpResponse::HTTP_REASON_NOT_FOUND                       = "Not Found";
const std::string HttpResponse::HTTP_REASON_METHOD_NOT_ALLOWED              = "Method Not Allowed";
const std::string HttpResponse::HTTP_REASON_NOT_ACCEPTABLE                  = "Not Acceptable";
const std::string HttpResponse::HTTP_REASON_PROXY_AUTHENTICATION_REQUIRED   = "Proxy Authentication Required";
const std::string HttpResponse::HTTP_REASON_REQUEST_TIMEOUT                 = "Request Time-out";
const std::string HttpResponse::HTTP_REASON_CONFLICT                        = "Conflict";
const std::string HttpResponse::HTTP_REASON_GONE                            = "Gone";
const std::string HttpResponse::HTTP_REASON_LENGTH_REQUIRED                 = "Length Required";
const std::string HttpResponse::HTTP_REASON_PRECONDITION_FAILED             = "Precondition Failed";
const std::string HttpResponse::HTTP_REASON_REQUESTENTITYTOOLARGE           = "Request Entity Too Large";
const std::string HttpResponse::HTTP_REASON_REQUESTURITOOLONG               = "Request-URI Too Large";
const std::string HttpResponse::HTTP_REASON_UNSUPPORTEDMEDIATYPE            = "Unsupported Media Type";
const std::string HttpResponse::HTTP_REASON_REQUESTED_RANGE_NOT_SATISFIABLE = "Requested Range Not Satisfiable";
const std::string HttpResponse::HTTP_REASON_EXPECTATION_FAILED              = "Expectation Failed";
const std::string HttpResponse::HTTP_REASON_INTERNAL_SERVER_ERROR           = "Internal Server Error";
const std::string HttpResponse::HTTP_REASON_NOT_IMPLEMENTED                 = "Not Implemented";
const std::string HttpResponse::HTTP_REASON_BAD_GATEWAY                     = "Bad Gateway";
const std::string HttpResponse::HTTP_REASON_SERVICE_UNAVAILABLE             = "Service Unavailable";
const std::string HttpResponse::HTTP_REASON_GATEWAY_TIMEOUT                 = "Gateway Time-out";
const std::string HttpResponse::HTTP_REASON_VERSION_NOT_SUPPORTED           = "HTTP Version not supported";
const std::string HttpResponse::HTTP_REASON_UNKNOWN                         = "???";

const std::string& HttpResponse::ParseStatus(HttppStatus status)
{
	switch (status)
	{
	case HTTP_CONTINUE: 
		return HTTP_REASON_CONTINUE;
	case HTTP_SWITCHING_PROTOCOLS: 
		return HTTP_REASON_SWITCHING_PROTOCOLS;
	case HTTP_OK: 
		return HTTP_REASON_OK;
	case HTTP_CREATED: 
		return HTTP_REASON_CREATED;
	case HTTP_ACCEPTED: 
		return HTTP_REASON_ACCEPTED;
	case HTTP_NONAUTHORITATIVE:	
		return HTTP_REASON_NONAUTHORITATIVE;
	case HTTP_NO_CONTENT: 
		return HTTP_REASON_NO_CONTENT;
	case HTTP_RESET_CONTENT: 
		return HTTP_REASON_RESET_CONTENT;
	case HTTP_PARTIAL_CONTENT: 
		return HTTP_REASON_PARTIAL_CONTENT;
	case HTTP_MULTIPLE_CHOICES: 
		return HTTP_REASON_MULTIPLE_CHOICES;
	case HTTP_MOVED_PERMANENTLY: 
		return HTTP_REASON_MOVED_PERMANENTLY;
	case HTTP_FOUND: 
		return HTTP_REASON_FOUND;
	case HTTP_SEE_OTHER: 
		return HTTP_REASON_SEE_OTHER;
	case HTTP_NOT_MODIFIED: 
		return HTTP_REASON_NOT_MODIFIED;
	case HTTP_USEPROXY: 
		return HTTP_REASON_USEPROXY;
	case HTTP_TEMPORARY_REDIRECT: 
		return HTTP_REASON_TEMPORARY_REDIRECT;
	case HTTP_BAD_REQUEST: 
		return HTTP_REASON_BAD_REQUEST;
	case HTTP_UNAUTHORIZED: 
		return HTTP_REASON_UNAUTHORIZED;
	case HTTP_PAYMENT_REQUIRED: 
		return HTTP_REASON_PAYMENT_REQUIRED;
	case HTTP_FORBIDDEN: 
		return HTTP_REASON_FORBIDDEN;
	case HTTP_NOT_FOUND: 
		return HTTP_REASON_NOT_FOUND;
	case HTTP_METHOD_NOT_ALLOWED:
		return HTTP_REASON_METHOD_NOT_ALLOWED;
	case HTTP_NOT_ACCEPTABLE: 
		return HTTP_REASON_NOT_ACCEPTABLE;
	case HTTP_PROXY_AUTHENTICATION_REQUIRED: 
		return HTTP_REASON_PROXY_AUTHENTICATION_REQUIRED;
	case HTTP_REQUEST_TIMEOUT: 
		return HTTP_REASON_REQUEST_TIMEOUT;
	case HTTP_CONFLICT: 
		return HTTP_REASON_CONFLICT;
	case HTTP_GONE: 
		return HTTP_REASON_GONE;
	case HTTP_LENGTH_REQUIRED: 
		return HTTP_REASON_LENGTH_REQUIRED;
	case HTTP_PRECONDITION_FAILED: 
		return HTTP_REASON_PRECONDITION_FAILED;
	case HTTP_REQUESTENTITYTOOLARGE: 
		return HTTP_REASON_REQUESTENTITYTOOLARGE;
	case HTTP_REQUESTURITOOLONG: 
		return HTTP_REASON_REQUESTURITOOLONG;
	case HTTP_UNSUPPORTEDMEDIATYPE: 
		return HTTP_REASON_UNSUPPORTEDMEDIATYPE;
	case HTTP_REQUESTED_RANGE_NOT_SATISFIABLE: 
		return HTTP_REASON_REQUESTED_RANGE_NOT_SATISFIABLE;
	case HTTP_EXPECTATION_FAILED: 
		return HTTP_REASON_EXPECTATION_FAILED;
	case HTTP_INTERNAL_SERVER_ERROR: 
		return HTTP_REASON_INTERNAL_SERVER_ERROR;
	case HTTP_NOT_IMPLEMENTED: 
		return HTTP_REASON_NOT_IMPLEMENTED;
	case HTTP_BAD_GATEWAY: 
		return HTTP_REASON_BAD_GATEWAY;
	case HTTP_SERVICE_UNAVAILABLE:
		return HTTP_REASON_SERVICE_UNAVAILABLE;
	case HTTP_GATEWAY_TIMEOUT: 
		return HTTP_REASON_GATEWAY_TIMEOUT;
	case HTTP_VERSION_NOT_SUPPORTED: 
		return HTTP_REASON_VERSION_NOT_SUPPORTED;
	default: 
		return HTTP_REASON_UNKNOWN;
	}
}

}