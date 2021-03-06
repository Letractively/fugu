#include "webapplication.h"
#include "config.h"
#include "context.h"
#include "connection.h"
//#include "database.h"
#include "query.h"
#include "logger.h"
#include "redisconnectionpool.h"
#include "handler.h"
#include <boost/cstdint.hpp>
#include <boost/thread/thread.hpp>

namespace fugu {

WebApplication::WebApplication(const std::string& configPath)
	: _config(new Config(configPath))
	,_router(_config)
	,_acceptor(_service)
	,_registrator(_router)
    ,_redisDBPool(new RedisDBConnectionPool(_service))
{
	// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
	boost::asio::ip::tcp::resolver resolver(_service);
	boost::asio::ip::tcp::resolver::query query(_config->Host(), _config->Port());
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	_acceptor.open(endpoint.protocol());
	_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	_acceptor.bind(endpoint);
	_acceptor.listen();

	DoAccept();
}

WebApplication::~WebApplication()
{
	HandleStop();
}

void WebApplication::Run()
{
	// Create a pool of threads to run all of the io_services.
	boost::thread_group threads;

	// Create threads for read/write async operations
	for (std::size_t i = 0; i < _config->ThreadPoolSize(); ++i)
		threads.create_thread( boost::bind(&boost::asio::io_service::run, &_service));

    // wait for them
    threads.join_all();
}

void WebApplication::DoAccept()
{
	//ConnectionPtr conn(_connectionPool.construct<boost::asio::io_service&, Connection::RequestHandler>
			//(_service, boost::bind(&WebApplication::ProcessRequest, this,_1,_2)));

	// The next connection to be accepted.
	ConnectionPtr conn(new Connection(_service, boost::bind(&WebApplication::HandleRequest, this,_1,_2)));
	_acceptor.async_accept(conn->Socket(), boost::bind(&WebApplication::HandleAccept, this,
		boost::asio::placeholders::error, conn));
}

void WebApplication::HandleAccept(const boost::system::error_code& e, ConnectionPtr conn)
{
	if (!e) {
		Log("Accepted:" + conn->Address());
		conn->Dispatch();
	}

	DoAccept();
}

void WebApplication::HandleStop()
{
	_service.stop();
}

void WebApplication::HandleRequest(QueryPtr query, ConnectionPtr conn)
{
	try
	{
		//SessionPtr session = _sessionMgr.GetSession(query->SessionHash());
           
		//if(!session) {
			//UserPtr user = _userMgr.GetUser(query->UserHash());
			//session = _sessionMgr.CreateSession(user);
		//}

        Context* ctx = _ctxPool.construct();
        ctx->_connection = conn;
        ctx->_query = query;
        ctx->_config = _config;
        ctx->_session = SessionPtr();
        
        
        ContextPtr ctxPtr(ctx, 
                        boost::bind(&ContextPool::destroy, 
                        &_ctxPool, ctx));
        
		HandlerPtr handler = _router.Resolve(query);
        
        if(handler->UseRedisDB()) {
            _redisDBPool->Queque(ctxPtr, boost::bind(&Handler::Process, handler, _1));
            return;
        }
        else {
            handler->Process(ctxPtr);
        }
        
	}
	catch(std::exception& ex)
	{
		Log(ex.what());
	}
}

void WebApplication::HandleRedisConnection(ContextPtr ctx)
{
    //handler->Process(ctx);
}

}