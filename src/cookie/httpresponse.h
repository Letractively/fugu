#ifndef __FUGU_HTTP_RESPONSE__
#define __FUGU_HTTP_RESPONSE__

#include "httpmessage.h"
#include <string>
#include <streambuf>
#include <sstream>
#include <boost/asio.hpp>

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
	HttpResponse();
	virtual ~HttpResponse();
	void SetCookie(const std::string& name, const std::string& value);
	void DeleteCookie(const std::string& name);
	HttppStatus Status() const;
	void SetStatus(HttppStatus status);
	const boost::asio::streambuf& SendBuffer();

private:
	// Output buffer
	std::ostream _outstream;
	boost::asio::streambuf _outstreambuf;
	HttppStatus _status;
};

}

#endif