#include "pingcontroller.h"

namespace fugu {

ResponsePtr PingController::Get(QueryContextPtr ctx)
{
	return NULL;
}

ResponsePtr PingController::Put(QueryContextPtr ctx)
{
	return NULL;
}

ResponsePtr PingController::Delete(QueryContextPtr ctx)
{
	return NULL;
}

ResponsePtr PingController::Post(QueryContextPtr ctx)
{
	return NULL;
}

	
Controller* PingControllerFactory::CreateImpl(const std::string url)
{
	return new PingController();
}

const static std::string PING_RESOURCE = "ping.fsp";
const std::string& PingControllerFactory::ResourceUrl() const
{
	return PING_RESOURCE;
}

}