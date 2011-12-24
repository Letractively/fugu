#include "jsonmodel.h"
#include "dbpool.h"
#include "exception.h"
#include <boost/thread/locks.hpp>

namespace fugu {

JsonModel::JsonModel(const JsonObj& obj)
{
	_jsonObj = obj;
}

JsonModel::~JsonModel()
{
}

std::string JsonModel::JsonString() const
{
	return _jsonObj.jsonString(mongo::JsonStringFormat::JS);
}

const JsonObj& JsonModel::JsonObject() const
{
	return _jsonObj;
}

JsonModelCache::JsonModelCache(const std::string& ns, const std::string& idFieldName)
	:_ns(ns)
	,_idFieldName(idFieldName)
{
}

JsonModelCache::~JsonModelCache()
{
}

JsonModelPtr JsonModelCache::Create(const std::string& json)
{
	return CreateImpl(json);
}

JsonModelPtr JsonModelCache::GetById(const std::string& id) const
{
	boost::shared_lock<boost::shared_mutex> lock(_access);
	JsonModelMap::const_iterator iter = _models.find(id);

	if(iter != _models.end())
		return iter->second;

	return JsonModelPtr();
}

JsonModelMapIterator JsonModelCache::All()
{
	LoadAll();
	return JsonModelMapIterator(_models, _access);
}

JsonModelPtr JsonModelCache::CreateImpl(const std::string& json)
{
	try
	{
		JsonModelPtr jmodel(new JsonModel(mongo::fromjson(json)));

		const char* id = jmodel->JsonObject().getStringField(_idFieldName.c_str());
		if(id == NULL) {
			FUGU_THROW("json string '" + json + "' doesn't have id fiels('" + id+"')", 
						"JsonModelCache::CreateImpl");
		}

		DBConnectionPtr conn = DBPool::Get().Queue();

		// Get upgradable access
		boost::upgrade_lock<boost::shared_mutex> lock(_access);
		// Get exclusive access
		boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
		// Now we have exclusive access
		JsonModelMap::const_iterator iter = _models.find(id);
		if(iter == _models.end()) {
			// Model doesn't exists, creating new
			conn->insert(_ns, jmodel->JsonObject());
		}
		else { // Model already exists, updating...
			conn->update(_ns, QUERY(_idFieldName<<id), jmodel->JsonObject());
		}

		// Get error result from the last operation on this connection. 
		std::string error = conn->getLastError();
		if(!error.empty()) {
			FUGU_THROW(error, "JsonModelCache::CreateImpl");
		}

		return jmodel;
	}
	catch(Exception& ex)
	{
		throw ex;
	}
	catch(mongo::DBException& ex)
	{
		FUGU_THROW(ex.toString(), "JsonModelCache::CreateImpl");
	}
	catch(std::exception& ex)
	{
		FUGU_THROW(ex.what(), "JsonModelCache::CreateImpl");
	}
}

void JsonModelCache::LoadAll()
{
	JsonModelMap fromdb;
	std::auto_ptr<mongo::DBClientCursor> cursor =  
		DBPool::Get().Queue()->query(_ns, mongo::Query());

	//getLastError();
	while(cursor->more()) {
		JsonObj json = cursor->next();
		const char* id = json.getStringField(_idFieldName.c_str());

		if(id != NULL) {
			JsonModelPtr model(new JsonModel(json.copy()));
			fromdb.insert(std::make_pair<std::string, JsonModelPtr>(id, model));
		}
	}

	{
		// Get upgradable access
		boost::upgrade_lock<boost::shared_mutex> lock(_access);
		// Get exclusive access
		boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
		// Now we have exclusive access
		fromdb.swap(_models);
	}
}

}