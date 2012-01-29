#ifndef __FUGU_CONNECTION__
#define __FUGU_CONNECTION__

#include "prerequisites.h"
#include "httpparser.h"
#include "query.h"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
//#include <boost/lockfree/fifo.hpp>
//#include <boost/atomic.hpp>

namespace fugu {

enum ConnectionState
{

	CONTINUE_READ = 0,
	SEND_REPLY_AND_CLOSE,
	SEND_REPLY_AND_CONTINUE_READ
};


// Represents a single connection from a client.
class Connection : public boost::enable_shared_from_this<Connection>,
					private boost::noncopyable
{
public:
	friend class WebApplication;
	typedef boost::function< void(QueryPtr, ConnectionPtr)> RequestHandler;

	// Construct a connection with the given io_service.
	explicit Connection(boost::asio::io_service& io_service, RequestHandler handler);
	~Connection();
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
	// Get the socket associated with the connection.
	boost::asio::ip::tcp::socket& Socket() { return _socket; }
	// Read data from the socket
	void DoRecive();
	// Handle completion of a read operation.
	void HandleRecive(const boost::system::error_code& e, std::size_t bytesTransferred);
	// Write existsing buffer to the socket
	void DoSend(ReplyPtr reply);
	// Handle completion of a write operation.
	void HandleSend(const boost::system::error_code& error, ReplyPtr reply);

private:
	// Strand to ensure the connection's handlers are not called concurrently.
	boost::asio::io_service::strand _strand;
	// Socket for the connection.
	boost::asio::ip::tcp::socket _socket;
	// Buffer for incoming data.
	boost::array<char, 8192> _buffer;
	// Web sockets connection
	bool _webSocketsConnection;
	// Handler of the incoming data
	RequestHandler _requestHandler;
	// State of the conection
	ConnectionState _state;
	// Request parser
	HttpParser _parser;
	// Http request
	QueryPtr _query;
};

}

#endif
