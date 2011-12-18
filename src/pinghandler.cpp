#include "pingHandler.h"
#include "reply.h"
#include "query.h"
#include <sstream>

namespace fugu {

ReplyPtr PingHandler::Process(ContextPtr ctx)
{
	
	StringPtr ptr(new std::string(
		"<html><head><title>ping</title></head><body><h1>fugu service is running...</h1></body></html>"
	));
	return View(ptr);
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