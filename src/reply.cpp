#include "reply.h"

namespace fugu {

Reply::Reply()
	:_stream(&_streambuf)
{
}

Reply::Reply(const std::string& data)
	:_stream(&_streambuf)
{
	_stream << data;
}

Reply::~Reply()
{
}

boost::asio::streambuf& Reply::StreamBuffer()
{
	return _streambuf;
}

}