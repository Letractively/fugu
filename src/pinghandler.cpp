#include "pingHandler.h"
#include "response.h"
#include <sstream>

namespace fugu {

ResponsePtr PingHandler::OKResponse()
{
	std::string content =  "<html><head><title>ping</title></head><body><h1>fugu service rinning</h1></body></html>";
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

ResponsePtr PingHandler::Get(ContextPtr ctx)
{
	return OKResponse();
}

ResponsePtr PingHandler::Put(ContextPtr ctx)
{
	return OKResponse();
}

ResponsePtr PingHandler::Delete(ContextPtr ctx)
{
	return OKResponse();
}

ResponsePtr PingHandler::Post(ContextPtr ctx)
{
	return OKResponse();
}

	
Handler* PingHandlerFactory::CreateImpl(const std::string url)
{
	return new PingHandler();
}

const static std::string PING_RESOURCE = "/ping.fsp";
const std::string& PingHandlerFactory::ResourceUrl() const
{
	return PING_RESOURCE;
}

}