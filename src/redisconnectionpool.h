#ifndef __REDOS_CONNECTION_POOL_H__
#define __REDOS_CONNECTION_POOL_H__

#include <vector>
#include <boost/asio.hpp>
#include "redisconnection.h"

using boost::asio::ip::tcp;

namespace fugu {

class RedisDBConnectionPool : public boost::enable_shared_from_this<RedisDBConnectionPool>
                            ,private boost::noncopyable 
{
public:
    typedef boost::object_pool<RedisDBConnection> RedisDBConnectionMemoryPool;
    
    RedisDBConnectionPool(boost::asio::io_service& io_service);
    // boost::function<void(RedisDBConnectionPtr)> Connected
    RedisDBConnectionPtr GetConnection();
    
private:
    unsigned int expireSeconds;
	boost::asio::deadline_timer _timer;
    RedisDBConnectionMemoryPool _memorypool;
    boost::asio::io_service& _ioservice;
    std::vector<RedisDBConnectionPtr> _conns;
};

}

#endif