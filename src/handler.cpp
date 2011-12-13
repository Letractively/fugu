#include "handler.h"
#include "route.h"
#include <exception.h>

namespace fugu {

	Handler::Handler()
	{
	}

	Handler::~Handler()
	{
	}

	ResponsePtr Handler::View()
	{
		return NULL;
	}

	ResponsePtr Handler::PartialView()
	{
		return NULL;
	}

	ResponsePtr Handler::Json(const std::string json)
	{
		return NULL;
	}

	ResponsePtr Handler::Xml(const std::string xml)
	{
		return NULL;
	}

	HandlerPtr HandlerFactory::Create(RoutePtr route)
	{
		HandlerPtr handler(CreateImpl());
		handler->_name = route->HandlerName();
		handler->_viewName = route->ViewName();
		return handler;
	}

	bool HandlerFactory::HasRights(UserPtr user)
	{
		return true;
	}

}

