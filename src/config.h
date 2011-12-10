#ifndef __FUGU_CONFIG_H__
#define __FUGU_CONFIG_H__

#include "prerequisites.h"
#include <boost/property_tree/ptree.hpp>

namespace fugu {

class Config : private boost::noncopyable
{
public:
	Config(const std::string& file);
	~Config();

	unsigned int Port();
	unsigned int ThreadPool();

private:
	void SetDefault();

private:
	// property tree object
	boost::property_tree::ptree _pt;
};

}

#endif