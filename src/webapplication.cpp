#include "webapplication.h"
#include "connection.h"
#include "httprequest.h"
#include "httpparseradapter.h"
#include "response.h"
#include "logger.h"
#include <boost/cstdint.hpp>
#include <boost/thread/thread.hpp>

namespace fugu {

WebApplication::WebApplication(const std::string& address, const std::string& port, const std::string& root, std::size_t threadPoolSize)
	: _threadPoolSize(threadPoolSize)
		,_acceptor(_acceptorService)
		,_router(root)
		,_performServiceWork(_performService)
{
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

ConnectionState WebApplication::HandleRequestData(RequestBuffer data, std::size_t bytesTransferred,  Connection* conn)
{
	HttpRequest request;
	HttpParserAdapter parser;
	if(parser.ParseRequest(&request, data, bytesTransferred))
	{
		std::string content =  "<html><head><title>Created</title></head><body><h1>201 Created</h1></body></html>";

		std::ostringstream response;
		response<<"HTTP/1.0 200 OK\r\n"
				<<"Location: www.google.com\r\n"
				//<<"Content-Type: text/html; charset=UTF-8\r\n"
				//<<"Content-Length: "<<content.length()<<"\r\n"
				//<<"Set-Cookie: user=test"<<"\r\n"
				//<<"Set-Cookie: session=test"<<"\r\n"
				<<"\r\n"<<content<<"\r\n";

		Response* resp = new Response(response.str());
		conn->Send(resp);
		return  ConnectionState::SEND_REPLY_AND_CLOSE;
	}

	return ConnectionState::CONTINUE_READ;
}

}