#include "database.h"
#include "config.h"
#include "jsonmodel.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace fugu {

Database::Database(boost::asio::io_service& ioservice, ConfigPtr config)
	:expireSeconds(10)
	,_timer(ioservice, boost::posix_time::seconds(expireSeconds))
	,_views(new JsonModelStorage(config->ViewsTable(), "Name"))
{
	UpdateCache();

	_timer.async_wait(boost::bind(&Database::CacheExpired 
					,this
					,boost::asio::placeholders::error));
}

ViewsPtr Database::Views() const
{
	return _views;
}

void Database::UpdateCache()
{
	_views->LoadAll();
}

void Database::CacheExpired(const boost::system::error_code& e)
{
	UpdateCache();
	
	_timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(expireSeconds));

	_timer.async_wait(boost::bind(&Database::CacheExpired 
					,this
					,boost::asio::placeholders::error));
}

}