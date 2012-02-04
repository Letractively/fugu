#include "redisconnection.h"

namespace fugu {
   
RedisCommandContext::RedisCommandContext(RedisCompletedCallback completed)
    :_reply(NULL)
    ,_completed(completed)
{
}

RedisCommandContext::RedisCommandContext(RedisCompletedCallback completed, AsyncArg arg)
    :_reply(NULL)
    ,_completed(completed)
    ,_arg(arg)
{
}

RedisCommandContext::RedisCommandContext()
    :_reply(NULL)
{
}

RedisCommandContext::~RedisCommandContext()
{
    //TODO: free reply?
    //free(_reply);
}

redisReply* RedisCommandContext::Reply() const
{
    return _reply;
}
    
AsyncArg RedisCommandContext::Arg() const
{
    return _arg;
}

void RedisCommandContext::NotifiCompleted()
{
    //_completed(shared_from_this());
    _completed(this);
}


RedisDBConnection::RedisDBConnection(boost::asio::io_service& io_service)
    : socket_(io_service)
    ,_strand(io_service)
{
    context_ = redisAsyncConnect("127.0.0.1", 6379);
    //context_->onConnect
    if(context_->err) {
            /* Let *ac leak for now... */
            printf("Error: %s\n", context_->errstr);
            return;
    }
    
	/*hiredis already connected
	 *use the existing native socket
	 */
	socket_.assign(boost::asio::ip::tcp::v4(),context_->c.fd);

	/*register hooks with the hiredis async context*/
	context_->ev.addRead = call_C_addRead;
	context_->ev.delRead = call_C_delRead;
	context_->ev.addWrite = call_C_addWrite;
	context_->ev.delWrite = call_C_delWrite;
	context_->ev.cleanup = call_C_cleanup;

	/*I don't know whether this even gets used, but...*/
	context_->ev.data = context_;

	/*C wrapper functions will use this
	 *pointer to call class members.
	 *fortunately hiredis doesn't use the data field.
	 *see line 70 of async.h
	 */
	context_->data = this;
}

RedisDBConnection::~RedisDBConnection()
{
    redisAsyncDisconnect(context_);
}

int RedisDBConnection::AsyncCommand(RedisCompletedCallback callback, AsyncArg arg, const char *format, ...)
{
    va_list ap;
    int status;
    va_start(ap,format);
            
    RedisCommandContext* cmdCtx = _pool.construct(callback);
    status = redisvAsyncCommand(context_, &RedisDBConnection::OnCommandCompleted 
                                ,cmdCtx ,format,ap);
    va_end(ap);
    return status;
}

int RedisDBConnection::AsyncCommand(RedisCompletedCallback callback, const char *format, ...)
{
    va_list ap;
    int status;
    va_start(ap,format);
      
    RedisCommandContext* cmdCtx = _pool.construct();
    status = redisvAsyncCommand(context_, &RedisDBConnection::OnCommandCompleted, 
                                cmdCtx ,format,ap);
    
    va_end(ap);
    return status;
}

int RedisDBConnection::AsyncCommand(const char *format, ...)
{
    va_list ap;
    int status;
    va_start(ap,format);
    status = redisvAsyncCommand(context_,NULL, NULL ,format,ap);
    va_end(ap);
    return status;
}

void RedisDBConnection::OnConnectedCallback(redisAsyncContext *c)
{
    RedisDBConnection* conn = reinterpret_cast<RedisDBConnection*>(c->data);
    //conn->OnConnected()
}
void RedisDBConnection::OnCommandCompleted(redisAsyncContext *c, void *reply, void *privdata)
{
    RedisDBConnection* conn = reinterpret_cast<RedisDBConnection*>(c->data);
    
    if(privdata) 
    {
        //TODO: and dynamic cast
        RedisCommandContext* cmd = reinterpret_cast<RedisCommandContext*>(privdata);
        if(!cmd->_completed.empty())
        {
            cmd->_reply = reinterpret_cast<redisReply*>(reply);
            cmd->NotifiCompleted();
        }
        
        conn->_pool.destroy(cmd);
    }  
}

void RedisDBConnection::operate()
{
	if(read_requested_ && !read_in_progress_) {    
		read_in_progress_ = true;
		socket_.async_read_some(boost::asio::null_buffers()
                                ,_strand.wrap( boost::bind(&RedisDBConnection::handle_read, this
                                                ,boost::asio::placeholders::error)));
	}

	if(write_requested_ && !write_in_progress_) {
		write_in_progress_ = true;
		socket_.async_write_some(boost::asio::null_buffers()
                ,_strand.wrap(boost::bind(&RedisDBConnection::handle_write, this
                    ,boost::asio::placeholders::error)));
	}
}

void RedisDBConnection::handle_read(boost::system::error_code ec)
{
	read_in_progress_ = false;
	if(!ec) {
		redisAsyncHandleRead(context_);
	}

        if (!ec || ec == boost::asio::error::would_block)
	        operate();
}

void RedisDBConnection::handle_write(boost::system::error_code ec)
{
	write_in_progress_ = false;
      	if(!ec) {
		redisAsyncHandleWrite(context_);
	}

	if (!ec || ec == boost::asio::error::would_block)
		operate();
}

void RedisDBConnection::add_read(void *privdata) 
{
	read_requested_ = true;
	operate();
}

void RedisDBConnection::del_read(void *privdata) 
{
	read_requested_ = false;
}

void RedisDBConnection::add_write(void *privdata) 
{
	write_requested_ = true;
	operate();
}

void RedisDBConnection::del_write(void *privdata) 
{
	write_requested_ = false;
}

void RedisDBConnection::cleanup(void *privdata) 
{
	/*Do I even need this?*/
	printf("cleanup called...\n");	
}

}

/*wrappers*/
extern "C" void call_C_addRead(void *privdata)
{
	redisAsyncContext *ac = (redisAsyncContext*)privdata;
	fugu::RedisDBConnection *C = reinterpret_cast<fugu::RedisDBConnection*>(ac->data);
	C->add_read(privdata);
}

extern "C" void call_C_delRead(void *privdata)
{
        redisAsyncContext *ac = (redisAsyncContext*)privdata;
        fugu::RedisDBConnection *C = reinterpret_cast<fugu::RedisDBConnection*>(ac->data);
        C->del_read(privdata);
}

extern "C" void call_C_addWrite(void *privdata)
{
        redisAsyncContext *ac = (redisAsyncContext*)privdata;
        fugu::RedisDBConnection *C = reinterpret_cast<fugu::RedisDBConnection*>(ac->data);
        C->add_write(privdata);
}

extern "C" void call_C_delWrite(void *privdata)
{
        redisAsyncContext *ac = (redisAsyncContext*)privdata;
        fugu::RedisDBConnection *C = reinterpret_cast<fugu::RedisDBConnection*>(ac->data);
        C->del_write(privdata);
}

extern "C" void call_C_cleanup(void *privdata)
{
        redisAsyncContext *ac = (redisAsyncContext*)privdata;
        fugu::RedisDBConnection *C = reinterpret_cast<fugu::RedisDBConnection*>(ac->data);
        C->cleanup(privdata);
}

/*end of wrappers*/
