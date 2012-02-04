#include "sender.h"
#include <boost/lexical_cast.hpp>
#include <boost/memory_order.hpp>

namespace redis4cpp {
    
Sender::Sender(boost::asio::io_service& io_service
                ,boost::asio::ip::tcp::socket& socket
                ,FifoCommands& sendedcommands
                ,boost::asio::io_service::strand& strand)

    : _socket(socket)
    ,_strand(strand)
    ,_sendedcommands(sendedcommands)
    ,_state(Unlocked)
{
}    

void Sender::AsyncCommand(CommandBase* cmd)
{
    DoSend(cmd);
}

void Sender::HandleSended(const boost::system::error_code& error, CommandBase* cmd)
{
    _state.store(Unlocked);
    
    if (!error)
    {
        // Add to sended commands queue, this command is next to respond result
        _sendedcommands.enqueue(cmd);
        
        DoSend();
    }
    else
    {
        //delete cmd;
    }
}

void Sender::DoSend(CommandBase* cmd)
{    

    if(cmd != NULL)
        _tosendcommands.enqueue(cmd);

    // Compare current value with expected, change it to desired if matches. 
    // Returns true if an exchange has been performed, and always writes 
    // the previous value back in expected.
    
    if(_state.exchange(Locked, boost::memory_order_acquire) == Locked)
    //if(_state.compare_exchange_strong(expected, 1, boost::memory_order_acquire))
    {
        CommandBase* tosend;
        if(_tosendcommands.dequeue(tosend)) {
            boost::asio::async_write(_socket,
                                boost::asio::buffer(tosend->OutputBuffer().Str()),
                                _strand.wrap(boost::bind(&Sender::HandleSended, this,
                                    boost::asio::placeholders::error, tosend)));
        }
        
    }
}

}

