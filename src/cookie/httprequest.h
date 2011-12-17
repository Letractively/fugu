#ifndef __FUGU_HTTP_REQUEST__
#define __FUGU_HTTP_REQUEST__

#include "httpmessage.h"
#include <boost/noncopyable.hpp>
namespace fugu {

enum HttpMethods { 
	HTTP_DELETE	= 0,
	HTTP_GET,
	HTTP_POST,
	HTTP_PUT,
	NOT_SUPPORTED
};

typedef std::map<std::string, std::string> QueryParams;
typedef ConstMapIterator<QueryParams> HttpHeadersIterator;

// A request received from a client.
class HttpRequest : public HttpMessage, private boost::noncopyable
{
public:
	HttpRequest();
	~HttpRequest();

	// Returns HTTP method: GET, POST, PUT, etc
	HttpMethods Method() const;
	// Sets HTTP method
	void SetMethod(HttpMethods method);
	// Returns request URL
	const std::string& Url() const;
	// Sets request URL
	void SetUrl(const std::string& url);
	// Returts true, if web socket request
	bool IsWebSocket() const;

private:
	friend std::ostream &operator << (std::ostream &, HttpRequest const &);
	void WriteToStream(std::ostream &) const;

private:
	std::string _url;
	HttpMethods _method;
};

}

#endif