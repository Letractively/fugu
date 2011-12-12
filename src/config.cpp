#include "config.h"
#include "exception.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>

namespace fugu {

Config::Config(const std::string& filename)
{
	if(filename.empty())
		FUGU_THROW("Config file name is emty", "Config::Config");

	if (!boost::filesystem::exists(filename))
		FUGU_THROW("Can't find config file '+" + filename + "'", "Config::Config");

	boost::property_tree::read_json(filename, _pt);
}

Config::~Config()
{
}

std::string Config::Bind() const
{
	return _pt.get<std::string>("Service.Bind");
}

std::string Config::Port() const
{
	return _pt.get<std::string>("Service.Port");
}

unsigned int Config::ThreadPoolSize() const
{
	return _pt.get<unsigned int>("Service.ThreadPoolSize");
}

int Config::GetInt(const std::string& key, int _default) const
{
	return _pt.get<int>(key, _default);
}

unsigned int Config::GetUInt(const std::string& key, unsigned int _default) const
{
	return _pt.get<unsigned int>(key, _default);
}

bool Config::GetBool(const std::string& key, bool _default) const
{
	return _pt.get<bool>(key, _default);
}

std::string Config::GetString(const std::string& key, const std::string& _default) const
{
	return _pt.get<std::string>(key, _default);
}

boost::property_tree::ptree Config::PropertyTree() const 
{ 
	return _pt; 
}


}