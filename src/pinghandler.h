#ifndef __FUGU__PING_CONTROLER_H__
#define __FUGU__PING_CONTROLER_H__

#include "handler.h"
#include <boost/enable_shared_from_this.hpp>
#include <boost/pool/object_pool.hpp>

namespace fugu {

class PingHandler : public Handler
                    ,private boost::noncopyable
{
public:
	void ProcessImpl(ContextPtr ctx);
private:
    void RedisCommandReply(RedisCommandContext* ctx);
private:
    ContextPtr _context;
};

class PingHandlerFactory : public HandlerFactory
{
protected:
	Handler* CreateImpl();
    void DoDestroy(Handler* handler);
public:
	const std::string& Name() const;
    
private:
    typedef boost::object_pool<PingHandler> PingHandlerAllocator;
    PingHandlerAllocator _allocator;

};

}

#endif