#include "connection.h"
#include "logger.h"
#include "reply.h"
#include "query.h"
#include <streambuf>

namespace fugu {

Connection::Connection(boost::asio::io_service& io_service, RequestHandler handler)
  : _strand(io_service)
    ,_socket(io_service)
	,_requestHandler(handler)
	,_query(new Query)
	,_webSocketsConnection(false)
{
}

Connection::~Connection()
{
	Log("Connection destroyed");
}

std::string Connection::Address() const
{
	// Do all your accepting and other stuff here.
	boost::asio::ip::tcp::endpoint remote_ep = _socket.remote_endpoint();
	boost::asio::ip::address remote_ad = remote_ep.address();
	return remote_ad.to_string();
}

void Connection::Send(ReplyPtr reply)
{
	DoSend(reply);
}

void Connection::Dispatch()
{
	DoRecive();
}

void Connection::Close()
{
	boost::system::error_code ignored_ec;
	_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
}

void Connection::DoRecive()
{
	_socket.async_read_some(boost::asio::buffer(_buffer),
		_strand.wrap( boost::bind(&Connection::HandleRecive, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred)));	
}

// If an error occurs then no new asynchronous operations are started. This
// means that all shared_ptr references to the Connection object will
// disappear and the object will be destroyed automatically after this
// handler returns. The Connection class's destructor closes the socket.
void Connection::HandleRecive(const boost::system::error_code& error, std::size_t bytesTransferred)
{
	if(!error)
	{
		if(_webSocketsConnection) {
		}
		else {
			if(_parser.ParseRequest(_query, _buffer.data(), bytesTransferred))
			{
				//_webSocketsConnection = _request->IsWebSocket();
				_requestHandler(_query, shared_from_this());
			}
		}
	}
}

void Connection::DoSend(ReplyPtr reply)
{
	if(reply->Streamed())
	{
		// Write whatever message we have for the client.
		boost::asio::async_write(_socket, reply->ResponseStream(),
									_strand.wrap(boost::bind(&Connection::HandleSend, shared_from_this(), 
									boost::asio::placeholders::error, reply)));
	}
	else
	{
		// Write whatever message we have for the client.
		boost::asio::async_write(_socket, boost::asio::buffer(reply->Response()),
									_strand.wrap(boost::bind(&Connection::HandleSend, shared_from_this(), 
									boost::asio::placeholders::error, reply)));
	}
}


// No new asynchronous operations are started. This means that all shared_ptr
// references to the Connection object will disappear and the object will be
// destroyed automatically after this handler returns. The Connection class's
// destructor closes the socket.
void Connection::HandleSend(const boost::system::error_code& error, ReplyPtr reply)
{
	if (!error)
	{
		boost::system::error_code ignored_ec;
		_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
	}
}

}