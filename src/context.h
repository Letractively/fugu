#ifndef __FUGU_QUERY_CONTEXT__
#define __FUGU_QUERY_CONTEXT__

#include "prerequisites.h"
#include <iostream>
namespace fugu {

class Context : private boost::noncopyable
{
friend class WebApplication;
friend class RedisDBConnectionPool;

public:

    Context(){}
    /*
	Context(SessionPtr session, ConnectionPtr connection, 
            QueryPtr query, ConfigPtr config, RedisDBConnectionPoolPtr database)
		:_session(session)
		,_connection(connection)
		,_query(query)
		,_config(config)
		,_database(database)
	{}
     */

	virtual ~Context()
    {
        std::cout <<"Context dsstroeyd" << std::endl;
    }

	SessionPtr Session() const { return _session; }
	ConnectionPtr Connection() const { return _connection; }
	QueryPtr Query() const { return _query; }
	ConfigPtr Cfg() const { return _config; }
	RedisDBConnectionPtr RedisDb() const { return _redisDB; }

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
	RedisDBConnectionPtr _redisDB;
};

}

#endif