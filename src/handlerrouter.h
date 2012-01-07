#ifndef __FUGU_CONTROLER_MANAGER_H__
#define __FUGU_CONTROLER_MANAGER_H__

#include "prerequisites.h"
#include "route.h"
#include <boost/thread/shared_mutex.hpp>
#include <vector>
#include <map>

namespace fugu {

class HandlerFactory;
typedef boost::shared_ptr<HandlerFactory> HandlerFactoryPtr;
typedef std::map<std::string, HandlerFactoryPtr> HandlerFactories;

class HandlerRouter : private boost::noncopyable
{
public:
	HandlerRouter(ConfigPtr config);
	~HandlerRouter();
	// Registration for all factories should be when the application starts
	void RegisterFactory(HandlerFactory* factory);
	// Free lock
	ReplyPtr Route(ContextPtr ctx);

private:
	HandlerFactories _factories;
	Routes _routes;
};

}

#endif