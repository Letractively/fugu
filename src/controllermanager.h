#ifndef __FUGU_CONTROLER_MANAGER_H__
#define __FUGU_CONTROLER_MANAGER_H__

#include "prerequisites.h"
#include <vector>
#include <map>

namespace fugu {

class ControllerFactory;
typedef boost::shared_ptr<ControllerFactory> ControllerFactoryPtr;
typedef std::map<std::string, ControllerFactoryPtr> ControllerFactories;

class ControllerManager : private boost::noncopyable
{
public:
	ControllerManager();
	~ControllerManager();
	void RegisterFactory(ControllerFactory* factory);
	ResponsePtr ProcessRequest(QueryContextPtr ctx);
private:
	ControllerFactories _factories;
};

}

#endif