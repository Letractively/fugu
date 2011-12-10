#include "config.h"
#include <boost/property_tree/json_parser.hpp>

namespace fugu {

Config::Config(const std::string& filename)
{
	if(filename.empty()) {
		SetDefault();
	}

	boost::property_tree::read_json(filename, _pt);
}

Config::~Config()
{
}

boost::property_tree::ptree Config::PropertyTree() const 
{ 
	return _pt; 
}

}