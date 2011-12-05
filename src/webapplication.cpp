#include "webapplication.h"
#include "querycontext.h"
#include "connection.h"
#include "httprequest.h"
#include "response.h"
#include "logger.h"
#include "pingcontroller.h"
#include <boost/cstdint.hpp>
#include <boost/thread/thread.hpp>

namespace fugu {

WebApplication::WebApplication(const std::string& address, const std::string& port, const std::string& root, std::size_t threadPoolSize)
	: _threadPoolSize(threadPoolSize)
		,_acceptor(_acceptorService)
		,_router(root)
		,_performServiceWork(_performService)
{
	_controllerMgr.RegisterFactory(new PingControllerFactory);

	// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
	boost::asio::ip::tcp::resolver resolver(_acceptorService);
	boost::asio::ip::tcp::resolver::query query(address, port);
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

	// Create acceptor thread, one thread to handle incoming connections
	threads.create_thread( boost::bind(&boost::asio::io_service::run, &_acceptorService));

	// Create threads for read/write async operations
	for (std::size_t i = 0; i < _threadPoolSize; ++i)
		threads.create_thread( boost::bind(&boost::asio::io_service::run, &_performService));

    // wait for them
    threads.join_all();
}

void WebApplication::DoAccept()
{
	// The next connection to be accepted.
	ConnectionPtr conn(new Connection(_performService, boost::bind(&WebApplication::ProcessRequest, this,_1,_2)));
	_acceptor.async_accept(conn->Socket(), boost::bind(&WebApplication::HandleAccept, this,
		boost::asio::placeholders::error, conn));
}

void WebApplication::HandleAccept(const boost::system::error_code& e, ConnectionPtr conn)
{
	if (!e) {
		Log("Accepted:" + conn->Address());
		conn->DoRun();
	}

	DoAccept();
}

void WebApplication::HandleStop()
{
	_acceptorService.stop();
	_performService.stop();
}

const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

void WebApplication::ProcessRequest(HttpRequestPtr req, ConnectionPtr conn)
{
	SessionPtr session = _sessionMgr.GetSession(req->GetCookie("FUGU_SESSION_HASH"));

	if(!session) {
		UserPtr user = _userMgr.GetUser(req->GetCookie("FUGU_USER_HASH"));
		session = _sessionMgr.CreateSession(user);
	}

	QueryContextPtr ctx(new QueryContext(session, conn, req));
	ResponsePtr resp = _controllerMgr.ProcessRequest(ctx);

	if(resp == NULL)
		conn->Close();
	else
		conn->Send(resp);
}

}