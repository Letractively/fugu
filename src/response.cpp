#include "response.h"

namespace fugu {

Response::Response()
	:_stream(&_streambuf)
{
}

Response::Response(const std::string data)
	:_stream(&_streambuf)
{
	_stream << data;
}

boost::asio::streambuf& Response::StreamBuffer()
{
	return _streambuf;
}

Response::~Response()
{
}

}