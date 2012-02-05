#include "reciever.h"
#include <boost/lexical_cast.hpp>

const short multicast_port = 30001;

namespace redis4cpp {

Receiver::Receiver(boost::asio::io_service& io_service
        ,boost::asio::ip::tcp::socket& socket
        ,ReplyReceived received
        ,boost::asio::io_service::strand& strand)
    : _socket(socket)
    ,_received(received)
    ,_strand(strand)
{
}
  
void Receiver::HandleReceive(const boost::system::error_code& error, std::size_t bytes_recvd)
{
    if(!error)
    {
        _received(_buffer, bytes_recvd);
        
        DoReceieve();
    }
    else {
        std::cout << "Receiver::HandleReceive error: " << error.message() << std::endl;
    }
}
  
void Receiver::DoReceieve()
{    
    //boost::asio::async_read_until(_socket,
    _socket.async_read_some(
        boost::asio::buffer(_buffer),//"\r\n"
                _strand.wrap(boost::bind(&Receiver::HandleReceive, this, 
                        boost::asio::placeholders::error, 
                        boost::asio::placeholders::bytes_transferred)));
}

}

