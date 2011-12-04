#ifndef __FUGU__PING_CONTROLER_H__
#define __FUGU__PING_CONTROLER_H__

#include "controller.h"

namespace fugu {

class PingController : public Controller
{
public:
	PingController(){}
	virtual ~PingController(){}
	virtual ResponsePtr Get(QueryContextPtr ctx);
	virtual ResponsePtr Put(QueryContextPtr ctx);
	virtual ResponsePtr Delete(QueryContextPtr ctx);
	virtual ResponsePtr Post(QueryContextPtr ctx);
	const std::string ResourceUrl() const { return _resourceUrl; }

private:
	std::string _resourceUrl;
};

class PingControllerFactory : public ControllerFactory
{
protected:			
	virtual Controller* CreateImpl(const std::string url)=0;
public:
	virtual const std::string& ResourceUrl() const=0;

};

}

#endif