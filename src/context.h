#ifndef __FUGU_QUERY_CONTEXT__
#define __FUGU_QUERY_CONTEXT__

#include "prerequisites.h"

namespace fugu {

class Context : private boost::noncopyable
{
public:
	Context(SessionPtr session, ConnectionPtr connection, 
					HttpRequestPtr request);

	virtual ~Context();

	SessionPtr Session() const;
	HttpRequestPtr Request() const;
	ConnectionPtr Connection() const;

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