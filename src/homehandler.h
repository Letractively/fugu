#ifndef __FUGU_HOME_CONTROLER_H__
#define __FUGU_HOME_CONTROLER_H__

#include "Handler.h"

namespace fugu {

class HomeHandler : public Handler
{
public:
	virtual ResponsePtr Get(ContextPtr ctx);

private:
	ResponsePtr OKResponse();
};

class HomeHandlerFactory : public HandlerFactory
{
protected:			
	Handler* CreateImpl(const std::string url);
public:
	const std::string& ResourceUrl() const;

};

}

#endif