#include "registrator.h"
#include "handlerrouter.h"
#include "pingHandler.h"
#include "homeHandler.h"

namespace fugu {

Registrator::Registrator(HandlerRouter& HandlerMgr)
	:_HandlerMgr(HandlerMgr)
{
	_HandlerMgr.RegisterFactory(new PingHandlerFactory);
	_HandlerMgr.RegisterFactory(new HomeHandlerFactory);
}

Registrator::~Registrator()
{
}

}