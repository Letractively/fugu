#include "registrator.h"
#include "controllermanager.h"
#include "pingcontroller.h"
#include "homecontroller.h"

namespace fugu {

Registrator::Registrator(ControllerManager& controllerMgr)
	:_controllerMgr(controllerMgr)
{
	_controllerMgr.RegisterFactory(new PingControllerFactory);
	_controllerMgr.RegisterFactory(new HomeControllerFactory);
}

Registrator::~Registrator()
{
}

}