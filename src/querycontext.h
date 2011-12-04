#ifndef __FUGU_QUERY_CONTEXT__
#define __FUGU_QUERY_CONTEXT__

#include "prerequisites.h"
#include "httprequest.h"

namespace fugu {

class QueryContext : private boost::noncopyable
{
public:
	QueryContext(SessionPtr session, ConnectionPtr connection, HttpRequestPtr request)
		:_session(session)
		,_connection(connection)
		,_request(request)
		{}

	virtual ~QueryContext() {}
	SessionPtr Session() { return _session; } 
	HttpRequestPtr Request() { return _request; }
	ConnectionPtr Connection() const { return _connection; }

private:
	// User session
	SessionPtr _session;
	// Current connection
	ConnectionPtr _connection;
	// Processed request
	HttpRequestPtr _request;
};

}

#endif