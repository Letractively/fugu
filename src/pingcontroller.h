#ifndef __FUGU__PING_CONTROLER_H__
#define __FUGU__PING_CONTROLER_H__

#include "controller.h"

namespace fugu {

class PingController : public Controller
{
public:
	virtual ResponsePtr Get(QueryContextPtr ctx);
	virtual ResponsePtr Put(QueryContextPtr ctx);
	virtual ResponsePtr Delete(QueryContextPtr ctx);
	virtual ResponsePtr Post(QueryContextPtr ctx);

private:
	ResponsePtr OKResponse();
};

class PingControllerFactory : public ControllerFactory
{
protected:			
	Controller* CreateImpl(const std::string url);
public:
	const std::string& ResourceUrl() const;

};

}

#endif