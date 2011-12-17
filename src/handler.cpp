#include "handler.h"
#include "htmlreply.h"
#include "route.h"
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

ReplyPtr Handler::View(const std::string& html)
{
	return new HtmlReply(html);
}

ReplyPtr Handler::PartialView(const JsonObj& json)
{
	return NULL;
	//return new Reply(json.jsonString(mongo::JsonStringFormat::JS));
}

ReplyPtr Handler::PartialView(const std::string& json)
{
	return NULL;
	//return new Reply(json);
}

ReplyPtr Handler::Json(const std::string& json)
{
	return NULL;
	//return new Reply(json);
}

ReplyPtr Handler::Json(const JsonObj& json)
{
	return NULL;
	//return new Reply(json.jsonString(mongo::JsonStringFormat::JS));
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

