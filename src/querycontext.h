#ifndef __FUGU_QUERY_CONTEXT__
#define __FUGU_QUERY_CONTEXT__

#include "prerequisites.h"
#include "httprequest.h"
#include "HttpResponse.h"

namespace fugu {

class QueryContext
{
public:
	QueryContext() {}
	virtual ~QueryContext() {}
	SessionPtr Session() { return _session; } 
	const HttpRequest& Request() { return _request; }
	ConnectionPtr Connection() const { return _connection; }

private:
	// User session
	SessionPtr _session;
	// Current connection
	ConnectionPtr _connection;
	// Processed request
	HttpRequest _request;
};

}

#endif