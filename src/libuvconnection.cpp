#include "libuvconnection.h"
#include "logger.h"
#include "reply.h"
#include "query.h"
#include <streambuf>
#include <stdlib.h>

namespace fugu {

#define RESPONSE \
  "HTTP/1.1 200 OK\r\n" \
  "Content-Type: text/plain\r\n" \
  "Content-Length: 12\r\n" \
  "\r\n" \
  "hello world\n"
    
static uv_buf_t resbuf;

  
uv_buf_t on_alloc(uv_handle_t* client, size_t suggested_size) {
  uv_buf_t buf;
  buf.base = (char*)malloc(suggested_size);
  buf.len = suggested_size;
  return buf;
}
    
void after_write(uv_write_t* req, int status) {
  uv_close((uv_handle_t*)req->handle, NULL);
}

LibuvConnection::LibuvConnection(uv_stream_t* server, uv_loop_t* eventloop)
    :_query(new Query)
    ,_webSocketsConnection(false)
{
  resbuf.base = RESPONSE;
  resbuf.len = sizeof(RESPONSE);
  
    _handle.data = this;
    uv_tcp_init(eventloop, &_handle);
    int r = uv_accept(server, (uv_stream_t*)&_handle);
    uv_read_start((uv_stream_t*)&_handle, on_alloc, LibuvConnection::OnRead);
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
}

void LibuvConnection::Dispatch()
{
}

void LibuvConnection::OnRead(uv_stream_t* tcp, ssize_t nread, uv_buf_t buf)
{
    LibuvConnection* conn = reinterpret_cast<LibuvConnection*>(tcp->data);
    uv_write(
        &conn->write_req,
        (uv_stream_t*)&conn->_handle,
        &resbuf,
        1,
        after_write);
}

void LibuvConnection::Close()
{
}


}