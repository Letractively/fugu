#ifndef __REDOS_CONNECTION_POOL_H__
#define __REDOS_CONNECTION_POOL_H__

#include "prerequisites.h"
#include "redisconnection.h"
#include <vector>
#include <boost/asio.hpp>
#include <boost/lockfree/fifo.hpp>

using boost::asio::ip::tcp;

namespace fugu {

class RedisDBConnectionPool : public boost::enable_shared_from_this<RedisDBConnectionPool>
                            ,private boost::noncopyable 
{
public:
    typedef boost::object_pool<RedisDBConnection> RedisDBConnectionMemoryPool;
    typedef boost::lockfree::fifo<RedisDBConnection*> RedisDBConnectionQueque;
    
    RedisDBConnectionPool(boost::asio::io_service& io_service);
    // Queque connection to redis db
    void Queque(ContextPtr ctx, RedisConnectedCallback callback);
    
private:
    void OnFreeConnection(RedisDBConnectionPtr connection);
    
private:
    unsigned int expireSeconds;
	boost::asio::deadline_timer _timer;
    RedisDBConnectionMemoryPool _allocator;
    boost::asio::io_service& _ioservice;
    std::vector<RedisDBConnectionPtr> _conns;
    RedisDBConnectionQueque _connQueque;
};

}

#endif