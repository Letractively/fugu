#ifndef __FUGU_CONNECTION__
#define __FUGU_CONNECTION__

#include "prerequisites.h"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/atomic.hpp>
#include <boost/bind.hpp>
#include <boost/lockfree/fifo.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace fugu {

enum ConnectionState
{
	CONTINUE_READ = 0,
	SEND_REPLY_AND_CLOSE,
	SEND_REPLY_AND_CONTINUE_READ
};


class Response;

// Represents a single connection from a client.
class Connection : public boost::enable_shared_from_this<Connection>,
					private boost::noncopyable
{
public:
	friend class WebApplication;
	typedef boost::lockfree::fifo<Response*> SendQueue;
	typedef boost::function< ConnectionState(RequestBuffer, std::size_t, Connection*)> RequestHandler;

	// Construct a connection with the given io_service.
	explicit Connection(boost::asio::io_service& io_service, RequestHandler handler);
	// Client address
	std::string Address() const;
	// If true - web sockets connection, othewise http(s)
	bool IsWebSockets() const { return _webSocketsConnection; }
	// Put the data in the queue for sending
	void Send(Response* data);

private:
	// Get the socket associated with the connection.
	boost::asio::ip::tcp::socket& Socket() { return _socket; }
	// Start the first asynchronous operation for the connection.
	void DoRun();
	// Read data from the socket
	void DoRecive();
	// Handle completion of a read operation.
	void HandleRecive(const boost::system::error_code& e, std::size_t bytesTransferred);
	// Write existsing buffer to the socket
	void DoSend();
	// Handle completion of a write operation.
	void HandleSend(const boost::system::error_code& error, Response* resp);

private:
	// Strand to ensure the connection's handlers are not called concurrently.
	boost::asio::io_service::strand _strand;
	// Socket for the connection.
	boost::asio::ip::tcp::socket _socket;
	// Buffer for incoming data.
	boost::array<char, 8192> _buffer;
	// Send queue, lock-free queque
	SendQueue _toSendQueue;
	// > 0 - reading operation in the process
	boost::atomic_uchar _readers;
	// > 0 - sending operation in the process
	boost::atomic_uchar _senders;
	// Web sockets connection
	bool _webSocketsConnection;
	// Handler of the incoming data
	RequestHandler _requestHandler;
	// State of the conection
	ConnectionState _state;
};

}

#endif