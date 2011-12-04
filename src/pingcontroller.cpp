#include "pingcontroller.h"
#include "response.h"
#include <sstream>

namespace fugu {

ResponsePtr PingController::OKResponse()
{
	std::string content =  "<html><head><title>Created</title></head><body><h1>201 Created</h1></body></html>";
	std::ostringstream response;
	response<<"HTTP/1.0 200 OK\r\n"
			<<"Location: www.google.com\r\n"
			<<"Content-Type: text/html; charset=UTF-8\r\n"
			<<"Content-Length: "<<content.length()<<"\r\n"
			<<"Set-Cookie: user=test"<<"\r\n"
			<<"Set-Cookie: session=test"<<"\r\n"
			<<"\r\n"<<content<<"\r\n";

	return new Response(response.str());
}

ResponsePtr PingController::Get(QueryContextPtr ctx)
{
	return OKResponse();
}

ResponsePtr PingController::Put(QueryContextPtr ctx)
{
	return OKResponse();
}

ResponsePtr PingController::Delete(QueryContextPtr ctx)
{
	return OKResponse();
}

ResponsePtr PingController::Post(QueryContextPtr ctx)
{
	return OKResponse();
}

	
Controller* PingControllerFactory::CreateImpl(const std::string url)
{
	return new PingController();
}

const static std::string PING_RESOURCE = "/ping.fsp";
const std::string& PingControllerFactory::ResourceUrl() const
{
	return PING_RESOURCE;
}

}