#include "handler.h"
#include "reply.h"
#include "route.h"
#include <exception.h>
#include <dbclient.h>

namespace fugu {

Handler::Handler()
{
}

Handler::~Handler()
{
}

RoutePtr Handler::Route() const
{
	return _route;
}

ReplyPtr Handler::View(const std::string& page)
{
	return new Reply(page);
}

ReplyPtr Handler::PartialView(const JsonObj& json)
{
	return new Reply(json.jsonString(mongo::JsonStringFormat::JS));
}

ReplyPtr Handler::PartialView(const std::string& json)
{
	return new Reply(json);
}

ReplyPtr Handler::Json(const std::string& json)
{
	return new Reply(json);
}

ReplyPtr Handler::Json(const JsonObj& json)
{
	return new Reply(json.jsonString(mongo::JsonStringFormat::JS));
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

