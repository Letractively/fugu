#include "controllermanager.h"
#include "controller.h"
#include "exception.h"
#include "httprequest.h"
#include "querycontext.h"

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

ResponsePtr ControllerManager::ProcessRequest(const std::string url, QueryContextPtr ctx)
{
	ControllerFactories::iterator iter = _factories.find(url);
	if(iter != _factories.end())
	{
		ControllerFactoryPtr factory = iter->second;
		ControllerPtr controller = factory->Create(url);

		switch(ctx->Request()->Method())
		{
			case HTTPMethods::HTTP_DELETE:
				return controller->Delete(ctx);
			case HTTPMethods::HTTP_GET:
				return controller->Get(ctx);
			case HTTPMethods::HTTP_POST:
				return controller->Post(ctx);
		};
	}

	return NULL;
}

}