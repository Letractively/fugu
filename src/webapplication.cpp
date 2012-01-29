#include "webapplication.h"
#include "config.h"
#include "context.h"
#include "connection.h"
#include "query.h"
#include "logger.h"
#include <boost/cstdint.hpp>
#include <boost/thread/thread.hpp>
#include "libuvconnection.h"
//#include "database.h"

namespace fugu {

WebApplication::WebApplication(const std::string& configPath)
	: _config(new Config(configPath))
	,_router(_config)
	,_registrator(_router)
	//,_database(new Database(_service, _config))
{
	// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
    _eventloop = uv_default_loop();
    uv_tcp_init(_eventloop, (uv_tcp_t*)&_server);
    struct sockaddr_in address = uv_ip4_addr(_config->Host().c_str(), 9999);
    int r = uv_tcp_bind((uv_tcp_t*)&_server, address);

    if (r) {
        uv_err_t err = uv_last_error(_eventloop);
        fprintf(stderr, "bind: %s\n", uv_strerror(err));
        return;
    }

    _server.data = this;

    r = uv_listen(&_server, 128, WebApplication::OnConnection);

    if (r) {
        uv_err_t err = uv_last_error(uv_default_loop());
        fprintf(stderr, "listen: %s\n", uv_strerror(err));
        return;
    }
  
	//DoAccept();
}

WebApplication::~WebApplication()
{
	HandleStop();
}

void WebApplication::Run()
{
    // Block in the main loop
    uv_run(_eventloop);
}

void WebApplication::OnConnection(uv_stream_t* handle, int status)
{
    WebApplication* app = reinterpret_cast<WebApplication*>(handle->data);
    app->DoAccept();
}


void WebApplication::DoAccept()
{
    new LibuvConnection(&_server, _eventloop);
	//ConnectionPtr conn(_connectionPool.construct<boost::asio::io_service&, Connection::RequestHandler>
			//(_service, boost::bind(&WebApplication::ProcessRequest, this,_1,_2)));

	// The next connection to be accepted.
	//ConnectionPtr conn(new Connection(_service, boost::bind(&WebApplication::ProcessRequest, this,_1,_2)));
	//_acceptor.async_accept(conn->Socket(), boost::bind(&WebApplication::HandleAccept, this,
		//boost::asio::placeholders::error, conn));
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
	//_service.stop();
}

void WebApplication::ProcessRequest(QueryPtr query, ConnectionPtr conn)
{
	try
	{
		SessionPtr session = _sessionMgr.GetSession(query->SessionHash());

		//if(!session) {
			//UserPtr user = _userMgr.GetUser(query->UserHash());
			//session = _sessionMgr.CreateSession(user);
		//}

		ContextPtr ctx(new Context(SessionPtr(), conn, query, _config));//, _database));
		ReplyPtr reply = _router.Route(ctx);

		if(reply == NULL) 
			conn->Close();
		else
			conn->Send(reply);
	}
	catch(std::exception& ex)
	{
		Log(ex.what());
	}
}

}