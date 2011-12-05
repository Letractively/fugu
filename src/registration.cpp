#include "registrator.h"
#include "controllermanager.h"
#include "pingcontroller.h"

namespace fugu {

Registrator::Registrator(ControllerManager& controllerMgr)
	:_controllerMgr(controllerMgr)
{
	_controllerMgr.RegisterFactory(new PingControllerFactory);
}

Registrator::~Registrator()
{
}

}