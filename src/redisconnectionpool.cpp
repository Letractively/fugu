#include "redisconnectionpool.h"

namespace fugu {
   
RedisDBConnectionPool::RedisDBConnectionPool(boost::asio::io_service& ioservice)
    :_ioservice(ioservice)
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
