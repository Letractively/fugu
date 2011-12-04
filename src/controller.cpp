#include "controller.h"
#include <exception.h>

namespace fugu {

	Controller::Controller()
	{
	}

	Controller::~Controller()
	{
	}

	ResponsePtr Controller::Get(QueryContextPtr ctx)
	{
		FUGU_THROW("GET does't inplemented for handle resource: " + _resourceUrl, "Controller::Get");
	}

	ResponsePtr Controller::Put(QueryContextPtr ctx)
	{
		FUGU_THROW("PUT does't inplemented for handle resource: " + _resourceUrl, "Controller::Get");
	}

	ResponsePtr Controller::Delete(QueryContextPtr ctx)
	{
		FUGU_THROW("DELETE does't inplemented for handle resource: " + _resourceUrl, "Controller::Get");
	}

	ResponsePtr Controller::Post(QueryContextPtr ctx)
	{
		FUGU_THROW("POST does't inplemented for handle resource: " + _resourceUrl, "Controller::Get");
	}

	ResponsePtr Controller::View()
	{
		return NULL;
	}

	ResponsePtr Controller::PartialView()
	{
		return NULL;
	}

	ResponsePtr Controller::Json(const std::string json)
	{
		return NULL;
	}

	ResponsePtr Controller::Xml(const std::string xml)
	{
		return NULL;
	}

	ControllerPtr ControllerFactory::Create(const std::string url)
	{
		ControllerPtr controller(CreateImpl(url));
		controller->_resourceUrl = url;
		return controller;
	}

	bool ControllerFactory::HasRights(UserPtr user)
	{
		return true;
	}

}

