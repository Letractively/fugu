#ifndef __FUGU_HOME_CONTROLER_H__
#define __FUGU_HOME_CONTROLER_H__

#include "Handler.h"

namespace fugu {

class HomeHandler : public Handler
{
public:
	virtual ResponsePtr Process(ContextPtr ctx);
};

class HomeHandlerFactory : public HandlerFactory
{
protected:			
	Handler* CreateImpl();
public:
	const std::string& Name() const;

};

}

#endif