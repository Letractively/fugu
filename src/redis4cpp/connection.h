#ifndef __REDIS4CPP_CONNECTION_H__
#define __REDIS4CPP_CONNECTION_H__

#include "interface.h"
#include "sender.h"
#include "reciever.h"

namespace redis4cpp {

class Connection
{
public:
    Connection(boost::asio::io_service& io_service);

    // Add to lock-free queque, or send if curretly not processing
    void AsyncCommand(CommandBase* cmd);
  
private:
    boost::asio::io_service& _ioservice;
    boost::asio::io_service::strand strand_;
    boost::asio::ip::tcp::socket _socket;
    // Free-lock buffer commands of to send
    FifoCommands _sendedcommands;
    Sender _sender;
    Receiver _reciever;
};

}

#endif