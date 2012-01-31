#include "routeresolver.h"
#include "handler.h"
#include "route.h"
#include "exception.h"
#include "query.h"
#include "context.h"
#include "config.h"
#include "logger.h"
#include "redisconnectionpool.h"
#include <boost/thread/locks.hpp>
#include <boost/foreach.hpp>

namespace fugu {

RouteResolver::RouteResolver(ConfigPtr config)
{
	config->GetRoutes(_routes);
}

RouteResolver::~RouteResolver()
{
}

void RouteResolver::RegisterFactory(HandlerFactory* factory)
{
	HandlerFactories::iterator iter = _factories.find(factory->Name());
	if(iter != _factories.end()) {
		FUGU_THROW("HandlerFactory : '" + factory->Name() + "' already registered", 
					"RouteResolver::RegisterFactory");
	}

	_factories.insert(
		std::make_pair<std::string, HandlerFactoryPtr>(
							factory->Name(), 
							HandlerFactoryPtr(factory)));
}

HandlerPtr RouteResolver::Resolve(QueryPtr query)
{
	try
	{
		Routes::const_iterator riter = _routes.find(query->Uri());

		if(riter == _routes.end())
			FUGU_THROW("Route for url '" + query->Uri()+"' doesn't exists", "RouteResolver::Route");

		HandlerFactories::iterator fiter = _factories.find(riter->second->HandlerName());

		if(fiter == _factories.end())
			FUGU_THROW("Handler factory with name '" 
					+ riter->second->HandlerName() + "' doesn't exists", "RouteResolver::Route");

		HandlerFactoryPtr factory = fiter->second;
        // Create by route parameters
		HandlerPtr handler = factory->Create(riter->second);
        
        return handler;
            
	}
	catch(Exception& fe)
    {
        throw fe;
	}
	catch(std::exception& e)
    {
        FUGU_THROW(e.what() ,"RouteResolver::Route");
	}
}

}