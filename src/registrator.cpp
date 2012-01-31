#include "registrator.h"
#include "routeresolver.h"
#include "pinghandler.h"
//#include "dbviewhandler.h"
//#include "templatepagehandler.h"

namespace fugu {

Registrator::Registrator(RouteResolver& router)
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