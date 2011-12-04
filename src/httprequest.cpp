#include "httprequest.h"

namespace fugu {

HttpRequest::HttpRequest()
{
}

HttpRequest::~HttpRequest()
{
}

HTTPMethods HttpRequest::Method() const
{
	return _method;
}

void HttpRequest::SetMethod(HTTPMethods method)
{
	_method = method;
}

const std::string& HttpRequest::Url() const
{
	return _url;
}

void HttpRequest::SetUrl(const std::string& url)
{
	_url = url;
}

std::ostream &operator << (std::ostream& out, HttpRequest const & req)
{
	req.WriteToStream(out);
	return out;
}

void HttpRequest::WriteToStream(std::ostream& out) const
{
}

}