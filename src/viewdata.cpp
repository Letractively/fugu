#include "viewdata.h"
#include "dbpool.h"
#include <dbclient.h>

namespace fugu {

ViewData::ViewData(const mongo::BSONObj& obj)
	:_name(obj.getStringField("Name"))
	,_region(obj.getStringField("Region"))
	,_content(obj.getStringField("Content"))
	,_javascript(obj.getStringField("JavaScript"))
{
}

ViewData::ViewData(const std::string& name, const std::string& region, 
					const std::string& content, const std::string& javascript)
	:_name(name)
	,_region(region)
	,_content(content)
	,_javascript(javascript)
{
}

ViewData::~ViewData()
{
}

ViewDataPtr ViewDataManager::CreateView(const std::string& json)
{
	mongo::BSONObj obj = mongo::fromjson(json);
	return CreateView(obj);
}

ViewDataPtr ViewDataManager::GetView(const std::string& name)
{
	LoadViews();
	ViewsData::iterator iter = _views.find(name);
	if(iter != _views.end())
		return iter->second;

	return ViewDataPtr();
}

ViewsDataIterator ViewDataManager::GetViews()
{
	return ViewsDataIterator(_views);
}

ViewDataPtr ViewDataManager::CreateView(const mongo::BSONObj& obj)
{
	ViewDataPtr view; {
		// Get shared access
		boost::shared_lock<boost::shared_mutex> lock(_access);
		view = GetView(obj.getStringField("Name"));
	}

	if(!view.get()) {

		view.reset(new ViewData(obj));
		{
			// Get upgradable access
			boost::upgrade_lock<boost::shared_mutex> lock(_access);
			// Get exclusive access
			boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
			_views.insert(std::make_pair<std::string, ViewDataPtr>(view->Name(), view));
		}

		DBPool::Get().Queue()->insert("test.fugu.views", obj);
	}

	return view;
}

long ViewDataManager::LoadViews(long count)
{
	std::auto_ptr<mongo::DBClientCursor> cursor =  
		DBPool::Get().Queue()->query("test.fugu.views", mongo::Query());

	while(cursor->more()) {
		ViewDataPtr view(new ViewData(cursor->next()));
		_views.insert(std::make_pair<std::string, ViewDataPtr>(view->Name(), view));
	}
		
	return _views.size();
}

}