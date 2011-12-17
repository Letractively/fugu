#include "handlerrouter.h"
#include "handler.h"
#include "route.h"
#include "exception.h"
#include "query.h"
#include "context.h"
#include "config.h"
#include <boost/thread/locks.hpp>
#include <boost/foreach.hpp>

namespace fugu {

HandlerRouter::HandlerRouter(Config& config)
{
	config.GetRoutes(_routes);
}

HandlerRouter::~HandlerRouter()
{
}

void HandlerRouter::RegisterFactory(HandlerFactory* factory)
{
	HandlerFactories::iterator iter = _factories.find(factory->Name());
	if(iter != _factories.end()) {
		FUGU_THROW("HandlerFactory : '" + factory->Name() + "' already registered", 
					"HandlerRouter::RegisterFactory");
	}

	_factories.insert(
		std::make_pair<std::string, HandlerFactoryPtr>(
							factory->Name(), 
							HandlerFactoryPtr(factory)));
}

ReplyPtr HandlerRouter::Route(ContextPtr ctx)
{
	try
	{
		Routes::const_iterator riter = _routes.find(ctx->Query()->Url());

		if(riter == _routes.end())
			FUGU_THROW("Route for url '" + ctx->Query()->Url()+"' doesn't exists", "HandlerRouter::Route");

		HandlerFactories::iterator iter = _factories.find(riter->second->HandlerName());
		if(iter != _factories.end())
		{
			HandlerFactoryPtr factory = iter->second;
			HandlerPtr handler = factory->Create(riter->second);

			return handler->Process(ctx);

		}
	}
	catch(Exception& fe)
	{
		throw fe;
	}
	catch(std::exception& e)
	{
		FUGU_THROW(e.what()
					,"HandlerRouter::ProcessRequest");
	}

	return NULL;
}

}