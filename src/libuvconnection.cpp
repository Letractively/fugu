#include "libuvconnection.h"
#include "logger.h"
#include "reply.h"
#include "query.h"
#include <streambuf>

namespace fugu {

LibuvConnection::LibuvConnection(RequestHandler handler)
    :_query(new Query)
    ,_webSocketsConnection(false)
{
}

LibuvConnection::~LibuvConnection()
{
    Log("Connection destroyed");
}

std::string LibuvConnection::Address() const
{
	// Do all your accepting and other stuff here.();
	return "asdasd";
}

void LibuvConnection::Send(ReplyPtr reply)
{
	DoSend(reply);
}

void LibuvConnection::Dispatch()
{
	DoRecive();
}

void LibuvConnection::Close()
{
}

void LibuvConnection::DoRecive()
{	
}

// If an error occurs then no new asynchronous operations are started. This
// means that all shared_ptr references to the Connection object will
// disappear and the object will be destroyed automatically after this
// handler returns. The Connection class's destructor closes the socket.
void LibuvConnection::HandleRecive(std::size_t bytesTransferred)
{
    if(_webSocketsConnection) {
    }
    else {
        //if(_parser.ParseRequest(_query, _buffer.data(), bytesTransferred))
        //{
            //_webSocketsConnection = _request->IsWebSocket();
            //_requestHandler(_query, shared_from_this());
        //}
    }
}

void LibuvConnection::DoSend(ReplyPtr reply)
{
	if(reply->Streamed())
	{
	}
	else
	{
	}
}


// No new asynchronous operations are started. This means that all shared_ptr
// references to the Connection object will disappear and the object will be
// destroyed automatically after this handler returns. The Connection class's
// destructor closes the socket.
void LibuvConnection::HandleSend(ReplyPtr reply)
{
}

}