#ifndef __FUGU_WEB_SERVER__
#define __FUGU_WEB_SERVER__

#include "uv.h"
#include "prerequisites.h"
#include "session.h"
#include "user.h"
#include "handlerrouter.h"
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
    void ProcessRequest(QueryPtr request, ConnectionPtr conn);

    static void OnConnection(uv_stream_t* server_handle, int status);
    
private:
    uv_stream_t _server;
    uv_loop_t* _eventloop;
    
    // Connection pool
    ConnectionPool _connectionPool;
    // Fugu service configuration
    ConfigPtr _config;
    // Manager of the user sessions
    SessionManager _sessionMgr;
    //User manager
    UserManager _userMgr;
    // The handler for all incoming requests.
    HandlerRouter _router;
    Registrator _registrator;
    DatabasePtr _database;
};

}

#endif