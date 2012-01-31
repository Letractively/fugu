#ifndef __FUGU_REGISTRATOR_H__
#define __FUGU_REGISTRATOR_H__

#include "prerequisites.h"

namespace fugu {

// Factories registrator
class Registrator : private boost::noncopyable
{
public:
	Registrator(RouteResolver& router);
	~Registrator();

private:
	RouteResolver& _router;
};

}

#endif