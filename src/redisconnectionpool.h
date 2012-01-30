#ifndef __REDOS_CONNECTION_POOL_H__
#define __REDOS_CONNECTION_POOL_H__

#include <vector>
#include "redisconnection.h"

using boost::asio::ip::tcp;

namespace fugu {

class RedisDBConnectionPool : public boost::enable_shared_from_this<RedisDBConnectionPool>
                            ,private boost::noncopyable 
{
public:
    typedef boost::object_pool<RedisDBConnection> RedisDBConnectionMemoryPool;
    
    RedisDBConnectionPool(boost::asio::io_service& io_service);
    RedisDBConnectionPtr GetConnection();
    
private:
    RedisDBConnectionMemoryPool _memorypool;
    boost::asio::io_service& _ioservice;
    std::vector<RedisDBConnectionPtr> _conns;
};

}

#endif