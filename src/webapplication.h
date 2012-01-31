#ifndef __FUGU_WEB_SERVER__
#define __FUGU_WEB_SERVER__

#include "prerequisites.h"
#include "session.h"
#include "user.h"
#include "routeresolver.h"
#include "registrator.h"
#include "connection.h"
#include <boost/asio.hpp>
#include <boost/pool/object_pool.hpp>

namespace fugu {

enum ConnectionState;

/// The top-level class of the HTTP server.
class WebApplication : private boost::noncopyable
{
public:
	typedef boost::object_pool<Connection> ConnectionPool;
    typedef boost::object_pool<Context> ContextPool;

	// Construct the server to listen on the specified TCP address and port, and
	// serve up files from the given directory.
	explicit WebApplication(const std::string& configPath);
	~WebApplication();

	// Run the server's io_service loop.
	// Create one thread to handle incoming connections 
	// and _threadPoolSize threads to perform other async operations
	void Run();

private:
	// Initiate an asynchronous accept operation.
	void DoAccept();
	// Handle completion of an asynchronous accept operation.
	void HandleAccept(const boost::system::error_code& e, ConnectionPtr connection);
	// Handle a request to stop the server.
	void HandleStop();
	// Handle request data
	void HandleRequest(QueryPtr request, ConnectionPtr conn);
    //void HandleRedisConnection(QueryPtr query, ConnectionPtr conn);

private:
	// Fugu service configuration
	ConfigPtr _config;
	// The io_service used to handle asynchronous incoming connections, 
	// and perform asynchronous operations(read/write socket, process requests, backend calls, etc)
	boost::asio::io_service _service;
	// Acceptor used to listen for incoming connections.
	boost::asio::ip::tcp::acceptor  _acceptor;
	// Manager of the user sessions
	SessionManager _sessionMgr;
	//User manager
	UserManager _userMgr;
	// The handler for all incoming requests.
	RouteResolver _router;
	Registrator _registrator;
	DatabasePtr _database;
    // Pools
    RedisDBConnectionPoolPtr _redisDBPool;
	ConnectionPool _connectionPool;
    ContextPool _ctxPool;
};

}

#endif