#include "pinghandler.h"
#include "config.h"
#include "query.h"
#include "context.h"
#include <sstream>

namespace fugu {

ReplyPtr PingHandler::Process(ContextPtr ctx)
{
	StringPtr ptr(new std::string(
		"<html><head><title>ping</title></head><body><h1>fugu service "
		+ ctx->Cfg()->Version() 
		+ "</h1></body></html>"
	));

	return Html(ptr);
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