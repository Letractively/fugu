#ifndef __REDIS4CPP_INTERFACE_H__
#define __REDIS4CPP_INTERFACE_H__

#include <boost/any.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/lockfree/fifo.hpp>
#include <boost/atomic.hpp>
#include "bytebuffer.h"

namespace redis4cpp {

class CommandBase;
typedef boost::shared_ptr<CommandBase> CommandBasePtr;

typedef boost::lockfree::fifo<CommandBase*> FifoCommands;

class CommandBase : public boost::enable_shared_from_this<CommandBase>
{
public:
    typedef boost::function<void(CommandBasePtr)> CommandCompleted;
    //CommandBase(const std::string& command);
    CommandBase(const std::string& command, CommandCompleted completed);
    ~CommandBase() { std::cout << "destroy command" << std::endl; }
    void AddArgument(const std::string& arg);
    void AddArgument(boost::int16_t arg);
    void AddArgument(boost::int32_t arg);
    void AddArgument(boost::int64_t arg);
    void AddArgument(float arg);
    void AddArgument(double arg);
    
    const ByteBuffer& OutputBuffer();
    void SetResult(const std::string& result) { _result = result; }
    const std::string& Result() const { return _result; }
    void Completed();
    
private:
    boost::uint16_t _arguments;
    ByteBuffer _buffer;
    std::string _result;
    CommandCompleted _completed;
};

}

#endif