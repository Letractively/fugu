#include "reply.h"
#include "exception.h"

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
	FUGU_THROW("Virtual method 'Reply::ResponseStream' doesn't implemented", "Reply::ResponseStream");
}

const std::string& Reply::Response() const
{
	FUGU_THROW("Virtual method 'Reply::Response' doesn't implemented", "Reply::Response");
}

}