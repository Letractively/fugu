#ifndef __FUGU_WEB_SERVER__
#define __FUGU_WEB_SERVER__

#include "prerequisites.h"
#include "requesthrouter.h"
#include "session.h"
#include "user.h"
#include "controllermanager.h"
#include <boost/asio.hpp>

namespace fugu {

enum ConnectionState;

/// The top-level class of the HTTP server.
class WebApplication : private boost::noncopyable
{
public:
	// Construct the server to listen on the specified TCP address and port, and
	// serve up files from the given directory.
	explicit WebApplication(const std::string& address, const std::string& port, const std::string& root, std::size_t threadPoolSize);
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
	void ProcessRequest(HttpRequestPtr request, ConnectionPtr conn);

private:
	// The io_service used to handle asynchronous incoming connections(in single thread)
	boost::asio::io_service _acceptorService;
	// Acceptor used to listen for incoming connections.
	boost::asio::ip::tcp::acceptor  _acceptor;
	// The io_service used to perform asynchronous operations(read/write socket, process requests, backend calls, etc)
	boost::asio::io_service _performService;
	// The run() call may be kept running by creating an object of type io_service::work
	boost::asio::io_service::work _performServiceWork;
	// The number of threads that will call io_service::run().
	std::size_t _threadPoolSize;
	// The handler for all incoming requests.
	RequestRouter _router;
	// Manager of the user sessions
	SessionManager _sessionMgr;
	//User manager
	UserManager _userMgr;
	// Controller manager
	ControllerManager _controllerMgr;
};

}

#endif