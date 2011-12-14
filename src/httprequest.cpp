#include "httprequest.h"
#include <boost/algorithm/string.hpp>

namespace fugu {

HttpRequest::HttpRequest()
{
}

HttpRequest::~HttpRequest()
{
}

HttpMethods HttpRequest::Method() const
{
	return _method;
}

void HttpRequest::SetMethod(HttpMethods method)
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

const std::string WS_HEADER = "websocket";
bool HttpRequest::IsWebSocket() const
{
	std::string wsheader = GetHeader("Upgrade");
	bool identical = boost::iequals(wsheader, WS_HEADER);
	return identical;
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