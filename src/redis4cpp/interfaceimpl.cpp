#include "interface.h"
#include <boost/lexical_cast.hpp>

namespace redis4cpp {

    /*
CommandBase::CommandBase(const std::string& command)
{
    //"*3\r\n$3\r\nSET\r\n$5\r\nmykey\r\n$7\r\nmyvalue\r\n"
            
    AddArgument(command);
}
*/
CommandBase::CommandBase(const std::string& command, CommandCompleted completed)
:_completed(completed)
{
    AddArgument(command);
}

void CommandBase::AddArgument(const std::string& arg)
{
    _buffer.WriteString(arg + "\r\n");
}

void CommandBase::AddArgument(boost::int16_t arg)
{

}

void CommandBase::AddArgument(boost::int32_t arg)
{

}

void CommandBase::AddArgument(boost::int64_t arg)
{

}

void CommandBase::AddArgument(float arg)
{

}

void CommandBase::AddArgument(double arg)
{
}

const ByteBuffer& CommandBase::OutputBuffer()
{
    return _buffer;
}
    
void CommandBase::Completed()
{
    //std::cout << _buffer.Data() << ":\r\n" << _result << std::endl;
    //std::cout << _result << std::endl;
    if(!_completed.empty())
        _completed(shared_from_this());
}

}

