#include "dbpool.h"
#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <dbclient.h>

namespace fugu {

class DBPoolImpl : public DBPool
{
private:
	DBPoolImpl();
public:
	static DBPoolImpl* Instance();
	DBConnectionPtr Queue();
private:

#ifdef FUGU_MULTI_THREADING
	static boost::atomic<DBPoolImpl*> instance_;
	static boost::mutex instantiation_mutex;
#endif

	DBConnectionPtr _connection;
};

boost::atomic<DBPoolImpl*> DBPoolImpl::instance_(0);
boost::mutex DBPoolImpl::instantiation_mutex;

DBPoolImpl::DBPoolImpl()
	:_connection(new mongo::DBClientConnection)
{
}

DBConnectionPtr DBPoolImpl::Queue()
{
	// reconect to database
	_connection->connect("localhost");
	return _connection;
}

DBPoolImpl* DBPoolImpl::Instance()
{
#ifdef FUGU_MULTI_THREADING
	DBPoolImpl * tmp = instance_.load(boost::memory_order_consume);
	if (!tmp) 
	{
		boost::mutex::scoped_lock guard(instantiation_mutex);
		tmp = instance_.load(boost::memory_order_consume);
		if (!tmp) 
		{
			tmp = new DBPoolImpl;
			instance_.store(tmp, boost::memory_order_release);
		}
	}
	return tmp;
#else
	static DBPoolImpl instance;
	return &instance;
#endif
}


DBPool::DBPool()
{
}

DBPool& DBPool::Get()
{
	return *DBPoolImpl::Instance();
}

}