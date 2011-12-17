#include "webapplication.h"
#include "context.h"
#include "connection.h"
#include "query.h"
#include "logger.h"
#include <boost/cstdint.hpp>
#include <boost/thread/thread.hpp>

namespace fugu {

WebApplication::WebApplication(const std::string& configPath)
	: _config(configPath)
	,_router(_config)
	,_acceptor(_service)
	,_registrator(_router)
{
	// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
	boost::asio::ip::tcp::resolver resolver(_service);
	boost::asio::ip::tcp::resolver::query query(_config.Bind(), _config.Port());
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
	for (std::size_t i = 0; i < _config.ThreadPoolSize(); ++i)
		threads.create_thread( boost::bind(&boost::asio::io_service::run, &_service));

    // wait for them
    threads.join_all();
}

void WebApplication::DoAccept()
{
	// The next connection to be accepted.
	ConnectionPtr conn(new Connection(_service, boost::bind(&WebApplication::ProcessRequest, this,_1,_2)));
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
	_service.stop();
}

void WebApplication::ProcessRequest(QueryPtr query, ConnectionPtr conn)
{
	SessionPtr session = _sessionMgr.GetSession(query->SessionHash());

	if(!session) {
		UserPtr user = _userMgr.GetUser(query->UserHash());
		session = _sessionMgr.CreateSession(user);
	}

	ContextPtr ctx(new Context(session, conn, query));
	ReplyPtr reply = _router.Route(ctx);

	if(reply == NULL) 
		conn->Close();
	else
		conn->Send(reply);
}

}