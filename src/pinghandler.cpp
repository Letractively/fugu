#include "pinghandler.h"
#include "config.h"
#include "query.h"
#include "context.h"
#include "redisconnectionpool.h"
#include "connection.h"
#include <sstream>

namespace fugu {

void PingHandler::ProcessImpl(ContextPtr ctx)
{
    _context = ctx;
    ctx->RedisDb()->GetConnection()->AsyncCommand("SET key test");
    ctx->RedisDb()->GetConnection()->AsyncCommand(
                                boost::bind(&PingHandler::RedisCommandReply, this,  _1), this
                                ,"eval \"return {1,2,{3,'Hello World!'}}\" 0");
}
	
void PingHandler::RedisCommandReply(RedisCommandContext* ctx)
{
	StringPtr ptr(new std::string(
		"<html><head><title>ping</title></head><body><h1>fugu service "
    + std::string(ctx->Reply()->str)
		//+ ctx->Cfg()->Version() 
		+ "</h1></body></html>"
	));
   
    ReturnAndDestroy(Html(ptr), _context);
}

Handler* PingHandlerFactory::CreateImpl()
{
    return _allocator.construct();
}

void PingHandlerFactory::DoDestroy(Handler* handler)
{
    _allocator.destroy(static_cast<PingHandler*>(handler));
}

const std::string& PingHandlerFactory::Name() const
{
	static std::string PING_HANDLER_NAME = "pinghandler";
	return PING_HANDLER_NAME;
}

}