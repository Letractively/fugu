#include "reply.h"

namespace fugu {

Reply::Reply(ReplyType replyType)
{
}

Reply::~Reply()
{
}

ReplyType Reply::Type() const
{
	return _replyType;
}

void Reply::SetHeaders(StringPtr headers)
{
	_headers = headers;
}

StringPtr Reply::Headers() const
{
	return _headers;
}

boost::asio::streambuf& Reply::ResponseStream() const
{
	static boost::asio::streambuf streambuf;
	static std::ostream stream(&streambuf);

	return streambuf;
}

const std::string& Reply::Response() const
{
	static std::string empty = "";
	return empty;
}

}