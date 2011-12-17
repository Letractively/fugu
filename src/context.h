#ifndef __FUGU_QUERY_CONTEXT__
#define __FUGU_QUERY_CONTEXT__

#include "prerequisites.h"

namespace fugu {

class Context : private boost::noncopyable
{
public:
	Context(SessionPtr session, ConnectionPtr connection, QueryPtr query)
		:_session(session)
		,_connection(connection)
		,_query(query)
	{}

	virtual ~Context(){}

	SessionPtr Session() const { return _session; }
	ConnectionPtr Connection() const { return _connection; }
	QueryPtr Query() const { return _query; }

private:
	// User session
	SessionPtr _session;
	// Current connection
	ConnectionPtr _connection;
	// Processed query
	QueryPtr _query;
};

}

#endif