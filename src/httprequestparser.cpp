#include "httprequestparser.h"
#include "httprequest.h"

namespace fugu {

HttpRequestParser::HttpRequestParser()
{
}

HttpRequestParser::~HttpRequestParser()
{
}

boost::tribool Parse(HttpRequest& http_msg, boost::system::error_code& ec)
{
	boost::tribool rc = boost::indeterminate;
	return rc;
}

}