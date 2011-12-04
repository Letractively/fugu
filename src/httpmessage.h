#ifndef __FUGU_HTTP_MESSAGE__
#define __FUGU_HTTP_MESSAGE__

#include "iterators.h"
#include <string>
#include <map>
#include <boost/noncopyable.hpp>

namespace fugu {


typedef std::map<std::string, std::string> HttpHeaders;
typedef ConstMapIterator<HttpHeaders> HttpHeadersIterator;

typedef std::map<std::string, std::string> HttpCookies;
typedef MapIterator<HttpCookies> HttpCookiesIterator;

class HttpMessage
{
public:
	HttpMessage();
	virtual ~HttpMessage();

	// Returns the HTTP major version for this message.
	unsigned short MajorVersion() const;
	// Sets the HTTP major version for this message.
	void SetMajorVersion(unsigned short version);
	// Returns the HTTP minor version for this message.
	unsigned short MinorVersion() const;
	// Sets the HTTP minor version for this message.
	void SetMinorVersion(unsigned short version);

	// Returns the content length for this message,
	std::streamsize ContentLength() const;
	// Sets the content length for this message,
	void SetContentLength(std::streamsize contentLength);
	// Returns the content type for this message.
	const std::string& ContentType() const;
	// Sets the content type for this message.
	void SetContentType(const std::string& mediaType);
	/// Sets the value of the Connection header field.
	void SetKeepAlive(bool keepAlive);
	/// Returns true if
	bool KeepAlive() const;

	// Should return true if header with given name is exists
	bool HasHeader(const std::string& name) const;
	// Add new header
	void AddHeader(const std::string&, const std::string& value);
	// Returns header by name
	const std::string& GetHeader(const std::string& name) const;
	// Returns all headers
	HttpHeadersIterator GetHeaders();

	void AddCookie(const std::string& name, const std::string& value);
	// Should return true if cookie with given name is exists
	bool HasCookie(const std::string& name) const;
	// Returns cookie by name
	std::string GetCookie(const std::string& name) const;
	// Returns all cookies
	HttpCookiesIterator GetCookies();

protected:
	// HTTP version
	unsigned short _httpVersionMajor;
	unsigned short _httpVersionMinor;
	std::string _contentType;
	std::streamsize _contentLength;
	bool _keepAlive;
	HttpHeaders _headers;
	HttpCookies _cookies;
};

}

#endif