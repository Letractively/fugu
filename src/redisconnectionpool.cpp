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

void RedisDBConnectionPool::OnFreeConnection(RedisDBConnectionPtr  connection)
{
    _connQueque.enqueue(connection.get());
    connection.reset();
}

void RedisDBConnectionPool::Queque(ContextPtr ctx, RedisConnectedCallback callback)
{
    RedisDBConnectionPtr connectionPtr;
    RedisDBConnection* connection;
    
    if(_connQueque.empty())
    {
        connection = _allocator.construct(_ioservice);
    }
    else
    {
         if(!_connQueque.dequeue(connection)) 
         {
             connection = _allocator.construct(_ioservice);
         }
    }
    
    connectionPtr = RedisDBConnectionPtr(connection, 
                                boost::bind(&RedisDBConnectionPool::OnFreeConnection, 
                                this, connectionPtr));
            
    //return connectionPtr;
}

}
