#ifndef __FUGU_CONFIG_H__
#define __FUGU_CONFIG_H__

#include "prerequisites.h"
#include "stdheaders.h"
#include <boost/property_tree/ptree.hpp>

namespace fugu {

class Config : private boost::noncopyable
{
public:
	Config(const std::string& file);
	~Config();

	std::string Host() const;
	std::string Port() const;
	unsigned int ThreadPoolSize() const;
	void GetRoutes(Routes& routes);
	std::string PageTemplate() const;
	std::string ViewsTable() const;
	std::string UsersTable() const;
	
private:
	// property tree object
	boost::property_tree::ptree _pt;
};

}

#endif