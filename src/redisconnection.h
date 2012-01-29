#ifndef __HIREDIS_BOOSTASIO_H__
#define __HIREDIS_BOOSTASIO_H__

#include "prerequisites.h"
#include "hiredis/hiredis.h"
#include "hiredis/async.h"

#include <iostream>
#include <string>
#include <stdio.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/any.hpp>

using boost::asio::ip::tcp;

namespace fugu {

typedef boost::any AsyncArg;

typedef boost::function< void(RedisCommandContext*)> RedisCompletedCallback;

class RedisCommandContext  : public boost::enable_shared_from_this<RedisCommandContext>
                                ,private boost::noncopyable 
{
friend class RedisDBConnection;

public:
    RedisCommandContext(RedisCompletedCallback completed);
    RedisCommandContext(RedisCompletedCallback completed, AsyncArg arg);
    RedisCommandContext();
    ~RedisCommandContext();

    redisReply* Reply() const;
    AsyncArg Arg() const;
    
private:
    void NotifiCompleted();
    static void OnCommandCompleted(redisAsyncContext *c, void *r, void *privdata);
    
private:
    RedisCompletedCallback _completed;
    redisReply* _reply;
    AsyncArg _arg;
        
};

class RedisDBConnection : public boost::enable_shared_from_this<RedisDBConnection>
                        ,private boost::noncopyable 
{
public:
    RedisDBConnection(boost::asio::io_service& io_service);

    //void Connect(const std::string& host = "127.0.0.1", int port = 6379);
    // Execute query to Redis with result in callback
    int AsyncCommand(RedisCompletedCallback callback, AsyncArg arg, const char *format, ...);
    int AsyncCommand(RedisCompletedCallback callback, const char *format, ...);
    // Execute query to Redis withot result
    int AsyncCommand(const char *format, ...);
        
	void operate();

	void handle_read(boost::system::error_code ec);
    void handle_write(boost::system::error_code ec);
    void add_read(void *privdata);
    void del_read(void *privdata);
    void add_write(void *privdata);
    void del_write(void *privdata);
    void cleanup(void *privdata);

private:
    void NotifiCommandCompleted();
    
private:
    redisAsyncContext *context_;
    boost::asio::ip::tcp::socket socket_;
    bool read_requested_;
    bool write_requested_;
    bool read_in_progress_;
    bool write_in_progress_;
};

}

/*C wrappers for class member functions*/
extern "C" void call_C_addRead(void *privdata);
extern "C" void call_C_delRead(void *privdata);
extern "C" void call_C_addWrite(void *privdata);
extern "C" void call_C_delWrite(void *privdata);
extern "C" void call_C_cleanup(void *privdata);

#endif /*__HIREDIS_BOOSTASIO_H__*/