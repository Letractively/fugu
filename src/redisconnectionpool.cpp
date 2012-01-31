#include "redisconnectionpool.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace fugu {
   
RedisDBConnectionPool::RedisDBConnectionPool(boost::asio::io_service& ioservice)
    :_ioservice(ioservice)
    ,expireSeconds(10)
    ,_timer(ioservice)
{
}

RedisDBConnectionPtr RedisDBConnectionPool::GetConnection()
{
    RedisDBConnection* connection = _memorypool.construct(_ioservice);
    
    RedisDBConnectionPtr connectionPtr =
                            RedisDBConnectionPtr(connection, 
                                boost::bind(&RedisDBConnectionMemoryPool::destroy, 
                                &_memorypool, connection));
    
    _conns.push_back(connectionPtr);
            
    return connectionPtr;
}

}
