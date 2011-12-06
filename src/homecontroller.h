#ifndef __FUGU_HOME_CONTROLER_H__
#define __FUGU_HOME_CONTROLER_H__

#include "controller.h"

namespace fugu {

class HomeController : public Controller
{
public:
	virtual ResponsePtr Get(QueryContextPtr ctx);

private:
	ResponsePtr OKResponse();
};

class HomeControllerFactory : public ControllerFactory
{
protected:			
	Controller* CreateImpl(const std::string url);
public:
	const std::string& ResourceUrl() const;

};

}

#endif