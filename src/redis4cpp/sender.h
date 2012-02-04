#ifndef __REDIS4CPP_SENDER_H__
#define __REDIS4CPP_SENDER_H__

#include "interface.h"
#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

namespace redis4cpp {

const short multicast_port = 6379;

class Sender
{
friend class Connection;
public:
    Sender(boost::asio::io_service& io_service
            ,boost::asio::ip::tcp::socket& socket
            ,FifoCommands& sendedcommands
            ,boost::asio::io_service::strand& strand);

    // Add to lock-free queque, or send if curretly not processing
    void AsyncCommand(CommandBase* cmd);
  
private:
    void DoSend(CommandBase* cmd = NULL);
    void HandleSended(const boost::system::error_code& error, CommandBase* cmd);
    
private:
    boost::asio::io_service::strand& _strand;
    // Free-lock buffer commands of to send
    FifoCommands _tosendcommands;
    FifoCommands& _sendedcommands;
    boost::asio::ip::tcp::socket& _socket;
    
    typedef enum {Locked, Unlocked} LockState;
    volatile boost::atomic<LockState> _state;
};

}

#endif