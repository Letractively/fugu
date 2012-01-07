#include "registrator.h"
#include "handlerrouter.h"
#include "pingHandler.h"
#include "dbviewhandler.h"

namespace fugu {

Registrator::Registrator(HandlerRouter& router)
	:_router(router)
{
	_router.RegisterFactory(new PingHandlerFactory);
	_router.RegisterFactory(new DBViewHandlerFactory);
}

Registrator::~Registrator()
{
}

}