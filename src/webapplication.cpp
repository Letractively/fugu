#include "webapplication.h"
#include "querycontext.h"
#include "connection.h"
#include "httprequest.h"
#include "httpparseradapter.h"
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
	ConnectionPtr conn(new Connection(_performService, boost::bind(&WebApplication::HandleRequestData, this,_1,_2,_3)));
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

ConnectionState WebApplication::HandleRequestData(RequestBuffer data, std::size_t bytesTransferred,  ConnectionPtr conn)
{
	HttpRequestPtr request(new HttpRequest);
	HttpParserAdapter parser;
	if(parser.ParseRequest(request.get(), data, bytesTransferred))
	{
		SessionPtr session;
		std::string sessionId = request->GetCookie("FUGU_SESSION_HASH");
		if(!sessionId.empty()) {
				std::string login = request->GetCookie("FUGU_USER_HASH");
				UserPtr user = _userMgr.GetUser(login);
				session = _sessionMgr.CreateSession(user);
		}
		else {
			session = _sessionMgr.GetSession(sessionId);
		}

		QueryContextPtr queryCtx(new QueryContext(session, conn, request));
		ResponsePtr resp = _controllerMgr.ProcessRequest(request->Url(), queryCtx);
		conn->Send(resp);

		return  ConnectionState::SEND_REPLY_AND_CLOSE;
	}

	return ConnectionState::CONTINUE_READ;
}

}