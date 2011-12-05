#ifndef __FUGU_REGISTRATOR_H__
#define __FUGU_REGISTRATOR_H__

#include "prerequisites.h"

namespace fugu {

class Registrator : private boost::noncopyable
{
public:
	Registrator(ControllerManager& controllerMgr);
	~Registrator();

private:
	ControllerManager& _controllerMgr;
};

}

#endif