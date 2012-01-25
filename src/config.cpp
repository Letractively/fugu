#include "config.h"
#include "exception.h"
#include "route.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

namespace fugu {

Config::Config(const std::string& filename)
{
	if(filename.empty())
		FUGU_THROW("Config file name is emty", "Config::Config");

	//if (!boost::filesystem::exists(filename))
		//FUGU_THROW("Can't find config file '+" + filename + "'", "Config::Config");

	boost::property_tree::read_json(filename, _pt);
}

Config::~Config()
{
}

std::string Config::Host() const
{
	return _pt.get<std::string>("Service.Host");
}

std::string Config::Port() const
{
	return _pt.get<std::string>("Service.Port");
}

unsigned int Config::ThreadPoolSize() const
{
	return _pt.get<unsigned int>("Service.ThreadPoolSize");
}

void Config::GetRoutes(Routes& routes)
{
    BOOST_FOREACH(boost::property_tree::ptree::value_type& route, _pt.get_child("Service.Routes"))	
	{
		const boost::property_tree::ptree& values = route.second;

		routes.insert(std::make_pair<std::string, RoutePtr>(values.get<std::string>("route"), 
			RoutePtr(new Route(values.get<std::string>("handler"), values.get<std::string>("viewname", "default")))));
	}
}

std::string Config::Version() const
{
	return _pt.get<std::string>("Service.Version");
}

std::string Config::ViewsTable() const
{
	return _pt.get<std::string>("DB.Tables.ViewsTable");
}

std::string Config::UsersTable() const
{
	return _pt.get<std::string>("DB.Tables.UsersTable");
}

std::string Config::PageTemplate() const
{
	return _pt.get<std::string>("UI.PageTemplate");
}

}