#ifndef __REDIS4CPP_RECIEVER_H__
#define __REDIS4CPP_RECIEVER_H__

#include "interface.h"
#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

namespace redis4cpp {

class Receiver
{
friend class Connection;

public:
    Receiver(boost::asio::io_service& io_service
            ,boost::asio::ip::tcp::socket& socket
            ,FifoCommands& sendedcommands
            ,boost::asio::io_service::strand& strand);

private:
    void DoReceieve();
    void HandleReceive(const boost::system::error_code& error, std::size_t bytes_recvd);
    
private:
    // Strand to ensure the connection's handlers are not called concurrently.
    boost::asio::io_service::strand& _strand;
    // Free-lock buffer commands of to send
    FifoCommands& _sendedcommands;
    boost::asio::ip::tcp::socket& _socket;
    enum { max_length = 1024 };
    char data_[max_length];
};

}

#endif