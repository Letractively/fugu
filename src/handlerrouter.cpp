#include "handlerrouter.h"
#include "Handler.h"
#include "exception.h"
#include "httprequest.h"
#include "context.h"
#include <boost/thread/locks.hpp>

namespace fugu {

HandlerRouter::HandlerRouter()
{
}

HandlerRouter::~HandlerRouter()
{
}

void HandlerRouter::RegisterFactory(HandlerFactory* factory)
{
	HandlerFactories::iterator iter = _factories.find(factory->ResourceUrl());
	if(iter != _factories.end()) {
		FUGU_THROW("HandlerFactory : '" + factory->ResourceUrl() + "' already registered", 
					"HandlerRouter::RegisterFactory");
	}

	_factories.insert(
		std::make_pair<std::string, HandlerFactoryPtr>(
							factory->ResourceUrl(), 
							HandlerFactoryPtr(factory)));
}

ResponsePtr HandlerRouter::ProcessRequest(ContextPtr ctx)
{
	HandlerFactories::iterator iter = _factories.find(ctx->Request()->Url());
	if(iter != _factories.end())
	{
		HandlerFactoryPtr factory = iter->second;
		HandlerPtr Handler = factory->Create(ctx->Request()->Url());

		switch(ctx->Request()->Method())
		{
			case HTTPMethods::HTTP_DELETE:
				return Handler->Delete(ctx);
			case HTTPMethods::HTTP_GET:
				return Handler->Get(ctx);
			case HTTPMethods::HTTP_POST:
				return Handler->Post(ctx);
			default:
				FUGU_THROW("HTTP method does't support(support only the following methods: GET,POST,DELETE,PUT)"
							,"HandlerRouter::ProcessRequest");
		};
	}

	return NULL;
}

}