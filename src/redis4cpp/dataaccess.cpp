#include "dataaccess.h"
#include <boost/lexical_cast.hpp>
#include <boost/memory_order.hpp>

namespace redis4cpp {
    
DataAccess::DataAccess(boost::asio::io_service& io_service)
    :_ioservice(io_service)
    ,_socket(io_service)
    ,strand_(io_service)
    ,_sender(_ioservice, _socket, _sendedcommands, strand_)
    ,_reciever(_ioservice, _socket, _sendedcommands, strand_)
{
    using boost::asio::ip::tcp;
    
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(tcp::v4(), "127.0.0.1", "6379");
    tcp::resolver::iterator iterator = resolver.resolve(query);
    
    _socket.connect(iterator->endpoint());

    // Put the socket into non-blocking mode.
    tcp::socket::non_blocking_io non_blocking_io(true);
    _socket.io_control(non_blocking_io);
    
    _reciever.DoReceieve();
}

void DataAccess::AsyncCommand(CommandBase* cmd)
{
    _sender.AsyncCommand(cmd);
}

}

