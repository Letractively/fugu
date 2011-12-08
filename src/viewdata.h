#ifndef __FUGU_VIEW_DATA__
#define __FUGU_VIEW_DATA__

#include "prerequisites.h"
#include "iterators.h"
#include "stdheaders.h"
#include <boost/thread/shared_mutex.hpp>

namespace fugu {

class ViewData : private boost::noncopyable
{
friend class ViewDataManager;

private:
	ViewData(const mongo::BSONObj& obj);
	ViewData(const std::string& name, const std::string& region, 
			const std::string& content, const std::string& javascript);

public:
	virtual ~ViewData();
	const std::string& Name() const { return _name; }
	const std::string& Region() const { return _region; }
	const std::string& Content() const { return _content; }
	const std::string& JavaScript() const { return _javascript; }

private:
	// Header, center, top, left, etc
	std::string _name;
	std::string _region;
	std::string _content;
	std::string _javascript;
};

typedef std::map<std::string, ViewDataPtr> ViewsData;
typedef MapIterator<ViewsData> ViewsDataIterator;

class ViewDataManager
{
public:
	ViewDataManager(){}
	// Creates new user by json string, and add it to the database
	ViewDataPtr CreateView(const std::string& json);
	// Get user by login
	ViewDataPtr GetView(const std::string& login);
	// Get all users
	ViewsDataIterator GetViews();

private:
	// count == 0 - loads all views
	long LoadViews(long count=0);
	ViewDataPtr CreateView(const mongo::BSONObj& obj);

private:
	boost::shared_mutex _access;
	ViewsData _views;
};

}

#endif