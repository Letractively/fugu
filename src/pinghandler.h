#ifndef __FUGU__PING_CONTROLER_H__
#define __FUGU__PING_CONTROLER_H__

#include "Handler.h"

namespace fugu {

class PingHandler : public Handler
{
public:
	virtual ResponsePtr Get(ContextPtr ctx);
	virtual ResponsePtr Put(ContextPtr ctx);
	virtual ResponsePtr Delete(ContextPtr ctx);
	virtual ResponsePtr Post(ContextPtr ctx);

private:
	ResponsePtr OKResponse();
};

class PingHandlerFactory : public HandlerFactory
{
protected:			
	Handler* CreateImpl(const std::string url);
public:
	const std::string& ResourceUrl() const;

};

}

#endif