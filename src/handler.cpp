#include "Handler.h"
#include <exception.h>

namespace fugu {

	Handler::Handler()
	{
	}

	Handler::~Handler()
	{
	}

	ResponsePtr Handler::Get(ContextPtr ctx)
	{
		FUGU_THROW("GET does't inplemented for handle resource: " + _resourceUrl, "Handler::Get");
	}

	ResponsePtr Handler::Put(ContextPtr ctx)
	{
		FUGU_THROW("PUT does't inplemented for handle resource: " + _resourceUrl, "Handler::Get");
	}

	ResponsePtr Handler::Delete(ContextPtr ctx)
	{
		FUGU_THROW("DELETE does't inplemented for handle resource: " + _resourceUrl, "Handler::Get");
	}

	ResponsePtr Handler::Post(ContextPtr ctx)
	{
		FUGU_THROW("POST does't inplemented for handle resource: " + _resourceUrl, "Handler::Get");
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

	HandlerPtr HandlerFactory::Create(const std::string url)
	{
		HandlerPtr Handler(CreateImpl(url));
		Handler->_resourceUrl = url;
		return Handler;
	}

	bool HandlerFactory::HasRights(UserPtr user)
	{
		return true;
	}

}

