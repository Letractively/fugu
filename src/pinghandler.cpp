#include "pingHandler.h"
#include "reply.h"
#include "query.h"
#include <sstream>

namespace fugu {

ReplyPtr PingHandler::Process(ContextPtr ctx)
{
	std::string content =  "<html><head><title>ping</title></head><body><h1>fugu service is running...</h1></body></html>";
	std::ostringstream response;
	response<<"HTTP/1.0 200 OK\r\n"
			<<"Location: www.google.com\r\n"
			<<"Content-Type: text/html; charset=UTF-8\r\n"
			<<"Content-Length: "<<content.length()<<"\r\n"
			<<"Set-Cookie: user=test"<<"\r\n"
			<<"Set-Cookie: session=test"<<"\r\n"
			<<"\r\n"<<content<<"\r\n";

	return View(response.str());
}
	
Handler* PingHandlerFactory::CreateImpl()
{
	return new PingHandler();
}

const std::string& PingHandlerFactory::Name() const
{
	static std::string PING_HANDLER_NAME = "pinghandler";
	return PING_HANDLER_NAME;
}

}