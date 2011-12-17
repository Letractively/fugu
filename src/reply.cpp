#include "reply.h"

namespace fugu {

Reply::~Reply()
{
}

boost::asio::streambuf& Reply::ResponseStream() const
{
	return EmptyResponseStream();
}

const std::string& Reply::Response() const
{
	return EmptyResponse();
}

const std::string& Reply::EmptyResponse()
{
	static std::string empty = "";
	return empty;
}

boost::asio::streambuf& Reply::EmptyResponseStream()
{
	static boost::asio::streambuf streambuf;
	static std::ostream stream(&streambuf);

	return streambuf;
}

}