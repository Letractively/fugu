#include "connection.h"
#include "logger.h"
#include "response.h"
#include <streambuf>

namespace fugu {

Connection::Connection(boost::asio::io_service& io_service, RequestHandler handler)
  : _strand(io_service)
    ,_socket(io_service)
	,_requestHandler(handler)
	,_readers(0)
	,_senders(0)
{
}

std::string Connection::Address() const
{
	// Do all your accepting and other stuff here.
	boost::asio::ip::tcp::endpoint remote_ep = _socket.remote_endpoint();
	boost::asio::ip::address remote_ad = remote_ep.address();
	return remote_ad.to_string();
}

void Connection::Send(Response* resp)
{
	_toSendQueue.enqueue(resp);
	DoSend();
}

void Connection::DoRun()
{
	DoRecive();
}


void Connection::DoRecive()
{
	unsigned char expected = 0, desired = 1;
	// Compare current value with expected, change it to desired if matches. 
	// Returns true if an exchange has been performed, and always writes the previous value back in expected.
	//  _readers_ == 0 - no sender, othewise sender is exist
	// If expected == current_value then current_value = desired
	if(_readers.compare_exchange_strong(expected, desired)) 
	{
		_socket.async_read_some(boost::asio::buffer(_buffer),
			_strand.wrap( boost::bind(&Connection::HandleRecive, shared_from_this(),
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred)));
	}
	
}

// If an error occurs then no new asynchronous operations are started. This
// means that all shared_ptr references to the Connection object will
// disappear and the object will be destroyed automatically after this
// handler returns. The Connection class's destructor closes the socket.
void Connection::HandleRecive(const boost::system::error_code& error, std::size_t bytesTransferred)
{
	_readers.exchange(0);

	if(!error)
	{
		Log("HandleRecive: " + Address());

		_state = _requestHandler(_buffer.data(), bytesTransferred,  this);
		switch(_state)
		{
			case CONTINUE_READ:
				DoRecive();
				break;

			case SEND_REPLY_AND_CLOSE:
			case SEND_REPLY_AND_CONTINUE_READ:
				DoSend();
				break;
		};
	}
}

void Connection::DoSend()
{
	unsigned char expected = 0, desired = 1;
	// Compare current value with expected, change it to desired if matches. 
	// Returns true if an exchange has been performed, and always writes the previous value back in expected.
	//  _senders == 0 - no sender, othewise sender is exist
	// If expected == current_value then current_value = desired
	if(_senders.compare_exchange_strong(expected, desired))
	{
		Response* out;
		if(_toSendQueue.dequeue(out)) {
			// Write whatever message we have for the client.
			boost::asio::async_write(_socket, out->StreamBuffer(),
										_strand.wrap(boost::bind(&Connection::HandleSend, shared_from_this(), 
										boost::asio::placeholders::error, out)));
		}
	}
}


// No new asynchronous operations are started. This means that all shared_ptr
// references to the Connection object will disappear and the object will be
// destroyed automatically after this handler returns. The Connection class's
// destructor closes the socket.
void Connection::HandleSend(const boost::system::error_code& error, Response* resp)
{
	_senders.exchange(0);

	delete resp;

	if (!error)
	{
		Log("HandleWrite: " + Address());

		if(_state == SEND_REPLY_AND_CLOSE) {
			// Initiate graceful Connection closure.
			boost::system::error_code ignored_ec;
			_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
		}
		else {
			DoRecive();
			DoSend();
		}
	}
}

}