#ifndef __FUGU_DB_POOL__
#define __FUGU_DB_POOL__

#include "prerequisites.h"

namespace fugu {

typedef boost::shared_ptr<mongo::DBClientConnection> DBConnectionPtr;

class DBPool : private boost::noncopyable
{
protected:
	DBPool();
public:
	// Single instance
	static  DBPool& Get();
	// Returns free connection from pool, or lock current thread
	virtual DBConnectionPtr Queue()=0;
};

}

#endif