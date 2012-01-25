#ifndef __FUGU_QUERY_CONTEXT__
#define __FUGU_QUERY_CONTEXT__

#include "prerequisites.h"

namespace fugu {

class Context : private boost::noncopyable
{
public:
	Context(SessionPtr session, ConnectionPtr connection, QueryPtr query, ConfigPtr config)//, DatabasePtr database)
		:_session(session)
		,_connection(connection)
		,_query(query)
		,_config(config)
		//,_database(database)
	{}

	virtual ~Context(){}

	SessionPtr Session() const { return _session; }
	ConnectionPtr Connection() const { return _connection; }
	QueryPtr Query() const { return _query; }
	ConfigPtr Cfg() const { return _config; }
	//DatabasePtr Db() const { return _database; }

private:
	// User session
	SessionPtr _session;
	// Current connection
	ConnectionPtr _connection;
	// Processed query
	QueryPtr _query;
	// Configuration
	ConfigPtr _config;
	// Database
	//DatabasePtr _database;
};

}

#endif