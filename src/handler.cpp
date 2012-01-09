#include "handler.h"
#include "htmlreply.h"
#include "jsonreply.h"
#include "route.h"
#include "jsonmodel.h"
#include <exception.h>
#include <dbclient.h>

namespace fugu {

Handler::~Handler()
{
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
	ReplyPtr reply(new JsonReply(view->JsonStringPtr()));
	return reply;
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

HandlerPtr HandlerFactory::Create(RoutePtr route)
{
	HandlerPtr handler(CreateImpl());
	handler->_route = route;
	return handler;
}

bool HandlerFactory::HasRights(UserPtr user)
{
	return true;
}

}

