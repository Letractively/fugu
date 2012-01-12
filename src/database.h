#ifndef __FUGU_DATABASE_H__
#define __FUGU_DATABASE_H__

#include "prerequisites.h"
#include <boost/asio.hpp>

namespace fugu {

typedef JsonModelStoragePtr ViewsPtr;

class Database : private boost::noncopyable
{
public:
	Database(boost::asio::io_service& ioservice, ConfigPtr config);

public:
	ViewsPtr Views() const;

private:
	void UpdateCache();
	void CacheExpired(const boost::system::error_code& e);

private:
	unsigned int expireSeconds;
	ViewsPtr _views;
	boost::asio::deadline_timer _timer;
};

}

#endif