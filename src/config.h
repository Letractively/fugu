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

	std::string Bind() const;
	std::string Port() const;
	unsigned int ThreadPoolSize() const;

	int GetInt(const std::string& key, int _default) const;
	unsigned int GetUInt(const std::string& key, unsigned int _default) const;
	bool GetBool(const std::string& key, bool _default) const;
	std::string GetString(const std::string& key, const std::string& _default="") const;
	boost::property_tree::ptree Config::PropertyTree() const;

private:
	// property tree object
	boost::property_tree::ptree _pt;
};

}

#endif