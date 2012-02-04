#include "reciever.h"
#include <boost/lexical_cast.hpp>

const short multicast_port = 30001;

namespace redis4cpp {

Receiver::Receiver(boost::asio::io_service& io_service
        ,boost::asio::ip::tcp::socket& socket
        ,FifoCommands& sendedcommands
        ,boost::asio::io_service::strand& strand)
    : _socket(socket)
    ,_strand(strand)
    ,_sendedcommands(sendedcommands)
{
}
  
void Receiver::HandleReceive(const boost::system::error_code& error, std::size_t bytes_recvd)
{
    if(!error)
    {
        CommandBasePtr cmd;
        if(_sendedcommands.dequeue(cmd))
        {
            cmd->SetResult(data_);
            cmd->Completed();
            //strand_.wrap((boost::bind(&CommandBase::Completed, cmd)))();
        }

        DoReceieve();
    }
}
  
void Receiver::DoReceieve()
{
    _socket.async_read_some(
        boost::asio::buffer(data_, max_length),
            _strand.wrap(boost::bind(&Receiver::HandleReceive, this, 
                        boost::asio::placeholders::error, 
                        boost::asio::placeholders::bytes_transferred)));
}

}

