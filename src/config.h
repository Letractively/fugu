#ifndef __FUGU_CONFIG_H__
#define __FUGU_CONFIG_H__

#include "prerequisites.h"
#include "stdheaders.h"
#include "route.h"
#include <boost/property_tree/ptree.hpp>

namespace fugu {

class Config : private boost::noncopyable
{
public:
	Config(const std::string& file);
	~Config();

	std::string Bind() const;
	std::string Port() const;
	unsigned int ThreadPoolSize() const;
	void GetRoutes(Routes& routes);

private:
	// property tree object
	boost::property_tree::ptree _pt;
};

}

#endif