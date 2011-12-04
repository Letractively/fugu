#include "controller.h"
#include <exception>

namespace fugu {

	Controller::Controller()
	{
	}

	Controller::~Controller()
	{
	}

	ResponsePtr Controller::Get(QueryContextPtr ctx)
	{
		//throw std::exception("GET does't inplemented for handle resource: " + _resourceUrl);
		return NULL;
	}

	ResponsePtr Controller::Put(QueryContextPtr ctx)
	{
		//throw std::exception("GET does't inplemented for handle resource: " + _resourceUrl);
		return NULL;
	}

	ResponsePtr Controller::Delete(QueryContextPtr ctx)
	{
		//throw std::exception("GET does't inplemented for handle resource: " + _resourceUrl);
		return NULL;
	}

	ResponsePtr Controller::Post(QueryContextPtr ctx)
	{
		//throw std::exception("GET does't inplemented for handle resource: " + _resourceUrl);
		return NULL;
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
		return ControllerPtr();
	}

	bool ControllerFactory::HasRights(UserPtr user)
	{
		return true;
	}

}

