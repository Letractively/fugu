#ifndef __FUGU_CONTROLER_MANAGER_H__
#define __FUGU_CONTROLER_MANAGER_H__

#include "prerequisites.h"
#include "route.h"
#include <boost/thread/shared_mutex.hpp>
#include <vector>
#include <map>

namespace fugu {

typedef std::map<std::string, HandlerFactoryPtr> HandlerFactories;

class RouteResolver : private boost::noncopyable
{
public:
	RouteResolver(ConfigPtr config);
	~RouteResolver();
	// Registration for all factories should be when the application starts
	void RegisterFactory(HandlerFactory* factory);
	// Free lock
	HandlerPtr Resolve(QueryPtr query);

private:
	HandlerFactories _factories;
	Routes _routes;
};

}

#endif