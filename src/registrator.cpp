#include "registrator.h"
#include "handlerrouter.h"
#include "pinghandler.h"
//#include "dbviewhandler.h"
//#include "templatepagehandler.h"

namespace fugu {

Registrator::Registrator(HandlerRouter& router)
	:_router(router)
{
	_router.RegisterFactory(new PingHandlerFactory);
	//_router.RegisterFactory(new DBViewHandlerFactory);
	//_router.RegisterFactory(new TempaltePageHandlerFactory);
}

Registrator::~Registrator()
{
}

}