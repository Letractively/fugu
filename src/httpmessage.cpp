#include "httpmessage.h"

namespace fugu {

const std::string EMPTY_HEADER = "";
const std::string EMPTY_COOKIE = "";

HttpMessage::HttpMessage()
	:_httpVersionMajor(1)
	,_httpVersionMinor(1)
{
}

HttpMessage::~HttpMessage()
{
}

unsigned short HttpMessage::MajorVersion() const
{
	return _httpVersionMajor;
}

void HttpMessage::SetMajorVersion(unsigned short version)
{
	_httpVersionMajor = version;
}

unsigned short HttpMessage::MinorVersion() const
{
	return _httpVersionMinor;
}

void HttpMessage::SetMinorVersion(unsigned short version)
{
	_httpVersionMinor = version;
}

std::streamsize HttpMessage::ContentLength() const
{
	return _contentLength;
}

void HttpMessage::SetContentLength(std::streamsize contentLength)
{
	_contentLength = contentLength;
}

const std::string& HttpMessage::ContentType() const
{
	return _contentType;
}

void HttpMessage::SetContentType(const std::string& mediaType)
{
	_contentType = mediaType;
}

void HttpMessage::SetKeepAlive(bool keepAlive)
{
	_keepAlive = keepAlive;
}

bool HttpMessage::KeepAlive() const
{
	return _keepAlive;
}

bool HttpMessage::HasHeader(const std::string& name) const
{
	HttpHeaders::const_iterator iter = _headers.find(name);
	return iter != _headers.end();
}

void HttpMessage::AddHeader(const std::string& name, const std::string& value)
{
	_headers.insert(std::make_pair<std::string, std::string>(name, value));
}

const std::string& HttpMessage::GetHeader(const std::string& name) const
{
	HttpHeaders::const_iterator iter = _headers.find(name);
	return iter->second;
}

HttpHeadersIterator HttpMessage::GetHeaders()
{
	return HttpHeadersIterator(_headers);
}

void HttpMessage::AddCookie(const std::string& name, const std::string& value)
{
	HttpCookies::iterator iter = _cookies.find(name);
	if(iter != _cookies.end())
		iter->second = value;
	else
		_cookies.insert(std::make_pair<std::string, std::string>(name,value));
}

bool HttpMessage::HasCookie(const std::string& name) const
{
	HttpCookies::const_iterator iter = _cookies.find(name);
	return iter != _cookies.end();
}

std::string HttpMessage::GetCookie(const std::string& name) const
{
	HttpCookies::const_iterator iter = _cookies.find(name);
	if(iter == _cookies.end())
		return EMPTY_HEADER;

	return iter->second;
}

HttpCookiesIterator HttpMessage::GetCookies()
{
	return HttpCookiesIterator(_cookies);
}

}