#include "controllermanager.h"
#include "controller.h"
#include "exception.h"
#include "httprequest.h"
#include "querycontext.h"
#include <boost/thread/locks.hpp>

namespace fugu {

ControllerManager::ControllerManager()
{
}

ControllerManager::~ControllerManager()
{
}

void ControllerManager::RegisterFactory(ControllerFactory* factory)
{
	ControllerFactories::iterator iter = _factories.find(factory->ResourceUrl());
	if(iter != _factories.end()) {
		FUGU_THROW("ControllerFactory : '" + factory->ResourceUrl() + "' already registered", 
					"ControllerManager::RegisterFactory");
	}

	_factories.insert(
		std::make_pair<std::string, ControllerFactoryPtr>(
							factory->ResourceUrl(), 
							ControllerFactoryPtr(factory)));
}

ResponsePtr ControllerManager::ProcessRequest(QueryContextPtr ctx)
{
	ControllerFactories::iterator iter = _factories.find(ctx->Request()->Url());
	if(iter != _factories.end())
	{
		ControllerFactoryPtr factory = iter->second;
		ControllerPtr controller = factory->Create(ctx->Request()->Url());

		switch(ctx->Request()->Method())
		{
			case HTTPMethods::HTTP_DELETE:
				return controller->Delete(ctx);
			case HTTPMethods::HTTP_GET:
				return controller->Get(ctx);
			case HTTPMethods::HTTP_POST:
				return controller->Post(ctx);
			default:
				FUGU_THROW("HTTP method does't support(support only the following methods: GET,POST,DELETE,PUT)"
							,"ControllerManager::ProcessRequest");
		};
	}

	return NULL;
}

}