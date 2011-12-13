#include "context.h"
#include "session.h"
#include "httprequest.h"
#include "connection.h"

namespace fugu {

Context::Context(SessionPtr session, ConnectionPtr connection, 
							HttpRequestPtr request)
	:_session(session)
	,_connection(connection)
	,_request(request)
{
}

Context::~Context()
{
}

SessionPtr Context::Session() const
{ 
	return _session;
}

HttpRequestPtr Context::Request() const
{ 
	return _request; 

}
ConnectionPtr Context::Connection() const 
{ 
	return _connection; 
}

}