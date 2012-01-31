#include "handler.h"
#include "htmlreply.h"
#include "jsonreply.h"
#include "route.h"
#include "exception.h"
#include "logger.h"
#include "context.h"
#include "connection.h"
//#include "jsonmodel.h"

namespace fugu {

Handler::Handler()
    :_inUse(false)
{
}

Handler::~Handler()
{
    Log("Handler destroyed");
}

void Handler::Process(ContextPtr ctx)
{
    try
    {
        ProcessImpl(ctx);
    }
	catch(Exception& fe)
    {
        throw fe;
        //ReturnAndDestroy(Error(fe, true), ctx);
	}
	catch(std::exception& e)
	{
        FUGU_THROW(e.what() ,"HandlerRouter::Route");
	}
}

bool Handler::Single()
{
    return true;
}

bool Handler::UseRedisDB()
{
    return true;
}

RoutePtr Handler::Route() const
{
	return _route;
}

ReplyPtr Handler::Html(StringPtr html)
{
	return ReplyPtr(new HtmlReply(html));
}

ReplyPtr Handler::PartialView(JsonModelPtr view)
{
	//ReplyPtr reply(new JsonReply(view->JsonStringPtr()));
	//return reply;
        return ReplyPtr();
}

ReplyPtr Handler::Json(StringPtr json)
{
	ReplyPtr reply(new JsonReply(json));
	return reply;
}

ReplyPtr Handler::Error(std::exception& ex, bool critical)
{
	JsonReplyPtr reply(new JsonReply());
	reply->SetError(ex.what(), critical);
	return reply;
}

static ReplyPtr Error(Exception& ex, bool critical)
{
	JsonReplyPtr reply(new JsonReply());
	reply->SetError(ex.what(), critical);
	return reply;
}

void Handler::InUse(bool state)
{
    _inUse = state;
}

bool Handler::InUse() const
{
    return _inUse;
}

void Handler::Return(ReplyPtr reply, ContextPtr ctx)
{
    ctx->Connection()->Send(reply);
}

void Handler::ReturnAndDestroy(ReplyPtr reply, ContextPtr ctx)
{
    ctx->Connection()->Send(reply);
    if(!OnDestroy.empty())
        OnDestroy(this);
}
    
HandlerPtr HandlerFactory::Create(RoutePtr route)
{
	HandlerPtr handler(CreateImpl());
	handler->_route = route;
    handler->OnDestroy = boost::bind(&HandlerFactory::DoDestroy, this, _1);
	return handler;
}

bool HandlerFactory::HasRights(UserPtr user)
{
	return true;
}

}

