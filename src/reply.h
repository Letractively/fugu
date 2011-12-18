#ifndef __FUGU_REPLY__
#define __FUGU_REPLY__

#include "prerequisites.h"
#include <streambuf>
#include <boost/asio.hpp>

namespace fugu {

enum ReplyType
{
	HTTP_REPLY,
	WEBSOCKET_REPLY
};

class Reply
{
public:
	Reply(ReplyType replyType);
	virtual ~Reply();
	ReplyType Type() const;

	// Sets headers in folowing format: Connection: close\r\nSet-Cookie: key=value;\r\n etc.
	void SetHeaders(StringPtr cookies);
	// Returns cookies headers
	StringPtr Headers() const;

	// Returns true if the reply is a stream output buffer
	virtual bool Streamed() const =0;
	// Stream output buffer
	virtual boost::asio::streambuf& ResponseStream() const;
	// String output buffer
	virtual const std::string& Response() const;

private:
	ReplyType _replyType;
	StringPtr _headers;
};

}

#endif