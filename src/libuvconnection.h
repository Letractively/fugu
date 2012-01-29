#ifndef __FUGU_LIBUV_CONNECTION__
#define __FUGU_LIBUV_CONNECTION__

#include "uv.h"
#include "prerequisites.h"
#include "httpparser.h"
#include "query.h"
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>

namespace fugu {


// Represents a single connection from a client.
class LibuvConnection : public boost::enable_shared_from_this<Connection>,
					private boost::noncopyable
{
public:
    friend class WebApplication;
    typedef boost::function< void(QueryPtr, ConnectionPtr)> RequestHandler;

    // Construct a connection with the given io_service.
    LibuvConnection(uv_stream_t* server, uv_loop_t* eventloop);
    ~LibuvConnection();
    // Client address
    std::string Address() const;
    // If true - web sockets connection, othewise http(s)
    bool IsWebSockets() const { return _webSocketsConnection; }
    // Put the data in the queue for sending
    void Send(ReplyPtr reply);
    // Start the first asynchronous operation for the connection.
    void Dispatch();
    // Close connection
    void Close();

private:
    static void OnRead(uv_stream_t* tcp, ssize_t nread, uv_buf_t buf);

private:
    uv_tcp_t _handle;
    uv_write_t write_req;
    // Web sockets connection
    bool _webSocketsConnection;
    // Handler of the incoming data
    RequestHandler _requestHandler;
    // Request parser
    HttpParser _parser;
    // HTTP request
    QueryPtr _query;
};

}

#endif