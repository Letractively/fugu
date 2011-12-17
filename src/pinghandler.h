#ifndef __FUGU__PING_CONTROLER_H__
#define __FUGU__PING_CONTROLER_H__

#include "handler.h"

namespace fugu {

class PingHandler : public Handler
{
public:
	ReplyPtr Process(ContextPtr ctx);
};

class PingHandlerFactory : public HandlerFactory
{
protected:			
	Handler* CreateImpl();
public:
	const std::string& Name() const;

};

}

#endif