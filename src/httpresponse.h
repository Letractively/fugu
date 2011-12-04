#ifndef __FUGU_HTTP_RESPONSE__
#define __FUGU_HTTP_RESPONSE__

#include "httpmessage.h"

namespace fugu {

// The status of the reply.
enum HttppStatus
{
	HTTP_CONTINUE                        = 100,
	HTTP_SWITCHING_PROTOCOLS             = 101,
	HTTP_OK                              = 200,
	HTTP_CREATED                         = 201,
	HTTP_ACCEPTED                        = 202,
	HTTP_NONAUTHORITATIVE                = 203,
	HTTP_NO_CONTENT                      = 204,
	HTTP_RESET_CONTENT                   = 205,
	HTTP_PARTIAL_CONTENT                 = 206,
	HTTP_MULTIPLE_CHOICES                = 300,
	HTTP_MOVED_PERMANENTLY               = 301,
	HTTP_FOUND                           = 302,
	HTTP_SEE_OTHER                       = 303,
	HTTP_NOT_MODIFIED                    = 304,
	HTTP_USEPROXY                        = 305,
	// UNUSED: 306
	HTTP_TEMPORARY_REDIRECT              = 307,
	HTTP_BAD_REQUEST                     = 400,
	HTTP_UNAUTHORIZED                    = 401,
	HTTP_PAYMENT_REQUIRED                = 402,
	HTTP_FORBIDDEN                       = 403,
	HTTP_NOT_FOUND                       = 404,
	HTTP_METHOD_NOT_ALLOWED              = 405,
	HTTP_NOT_ACCEPTABLE                  = 406,
	HTTP_PROXY_AUTHENTICATION_REQUIRED   = 407,
	HTTP_REQUEST_TIMEOUT                 = 408,
	HTTP_CONFLICT                        = 409,
	HTTP_GONE                            = 410,
	HTTP_LENGTH_REQUIRED                 = 411,
	HTTP_PRECONDITION_FAILED             = 412,
	HTTP_REQUESTENTITYTOOLARGE           = 413,
	HTTP_REQUESTURITOOLONG               = 414,
	HTTP_UNSUPPORTEDMEDIATYPE            = 415,
	HTTP_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
	HTTP_EXPECTATION_FAILED              = 417,
	HTTP_INTERNAL_SERVER_ERROR           = 500,
	HTTP_NOT_IMPLEMENTED                 = 501,
	HTTP_BAD_GATEWAY                     = 502,
	HTTP_SERVICE_UNAVAILABLE             = 503,
	HTTP_GATEWAY_TIMEOUT                 = 504,
	HTTP_VERSION_NOT_SUPPORTED           = 505
};

// A reply to be sent to a client.
class HttpResponse : public HttpMessage, 
						private boost::noncopyable
{
public:
	void SetCookie(const std::string& name, const std::string& value);
	void DeleteCookie(const std::string& name);

	static const std::string& ParseStatus(HttppStatus status);

private:
	// The content to be sent in the reply.
	std::string content;

public:
	static const std::string HTTP_REASON_CONTINUE;
	static const std::string HTTP_REASON_SWITCHING_PROTOCOLS;
	static const std::string HTTP_REASON_OK;
	static const std::string HTTP_REASON_CREATED;
	static const std::string HTTP_REASON_ACCEPTED;
	static const std::string HTTP_REASON_NONAUTHORITATIVE;
	static const std::string HTTP_REASON_NO_CONTENT;
	static const std::string HTTP_REASON_RESET_CONTENT;
	static const std::string HTTP_REASON_PARTIAL_CONTENT;
	static const std::string HTTP_REASON_MULTIPLE_CHOICES;
	static const std::string HTTP_REASON_MOVED_PERMANENTLY;
	static const std::string HTTP_REASON_FOUND;
	static const std::string HTTP_REASON_SEE_OTHER;
	static const std::string HTTP_REASON_NOT_MODIFIED;
	static const std::string HTTP_REASON_USEPROXY;
	static const std::string HTTP_REASON_TEMPORARY_REDIRECT;
	static const std::string HTTP_REASON_BAD_REQUEST;
	static const std::string HTTP_REASON_UNAUTHORIZED;
	static const std::string HTTP_REASON_PAYMENT_REQUIRED;
	static const std::string HTTP_REASON_FORBIDDEN;
	static const std::string HTTP_REASON_NOT_FOUND;
	static const std::string HTTP_REASON_METHOD_NOT_ALLOWED;
	static const std::string HTTP_REASON_NOT_ACCEPTABLE;
	static const std::string HTTP_REASON_PROXY_AUTHENTICATION_REQUIRED;
	static const std::string HTTP_REASON_REQUEST_TIMEOUT;
	static const std::string HTTP_REASON_CONFLICT;
	static const std::string HTTP_REASON_GONE;
	static const std::string HTTP_REASON_LENGTH_REQUIRED;
	static const std::string HTTP_REASON_PRECONDITION_FAILED;
	static const std::string HTTP_REASON_REQUESTENTITYTOOLARGE;
	static const std::string HTTP_REASON_REQUESTURITOOLONG;
	static const std::string HTTP_REASON_UNSUPPORTEDMEDIATYPE;
	static const std::string HTTP_REASON_REQUESTED_RANGE_NOT_SATISFIABLE;
	static const std::string HTTP_REASON_EXPECTATION_FAILED;
	static const std::string HTTP_REASON_INTERNAL_SERVER_ERROR;
	static const std::string HTTP_REASON_NOT_IMPLEMENTED;
	static const std::string HTTP_REASON_BAD_GATEWAY;
	static const std::string HTTP_REASON_SERVICE_UNAVAILABLE;
	static const std::string HTTP_REASON_GATEWAY_TIMEOUT;
	static const std::string HTTP_REASON_VERSION_NOT_SUPPORTED;
	static const std::string HTTP_REASON_UNKNOWN;
};

}

#endif