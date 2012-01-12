#include "jsonmodel.h"
#include "stringutils.h"
#include "exception.h"
#include <boost/thread/locks.hpp>

namespace fugu {

JsonModel::JsonModel()
	: BSONObj()
{
}

JsonModel::JsonModel(const JsonObj& obj)
	: BSONObj(obj)
{
}

JsonModel::~JsonModel()
{
}

std::string JsonModel::JsonString() const
{
	return jsonString(mongo::JsonStringFormat::JS);
}

StringPtr JsonModel::JsonStringPtr() const
{
	return SPtr(jsonString(mongo::JsonStringFormat::JS));
}

JsonModelStorage::JsonModelStorage(const std::string& ns, const std::string& idFieldName, GetConnectionHandler getconn)
	:GetConnection(getconn)
	,_ns(ns)
	,_fieldId(idFieldName)
{
}

JsonModelStorage::~JsonModelStorage()
{
}

JsonModelPtr JsonModelStorage::Create(const JsonObj& jsonObj)
{
	return CreateImpl(jsonObj);
}

JsonModelPtr JsonModelStorage::Create(const std::string& json)
{
	return CreateImpl(mongo::fromjson(json));
}

JsonModelPtr JsonModelStorage::GetById(const std::string& id) const
{
	boost::shared_lock<boost::shared_mutex> lock(_access);
	JsonModelMap::const_iterator iter = _models.find(id);

	if(iter != _models.end())
		return iter->second;

	return JsonModelPtr();
}

void JsonModelStorage::Delete(const std::string& id)
{
	DBConnectionPtr conn = GetConnection();
	conn->remove(_ns, QUERY(_fieldId << id));

	// Get upgradable access
	boost::upgrade_lock<boost::shared_mutex> lock(_access);
	// Get exclusive access
	boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
	_models.erase(id);
}

JsonModelMapIterator JsonModelStorage::All()
{
	return JsonModelMapIterator(_models, _access);
}

StringPtr JsonModelStorage::AllAsJson()
{
	boost::shared_lock<boost::shared_mutex> lock(_access);

	JsonModelMapIterator iter(_models);
	std::string json = "[";
	bool has = false;
	while(iter.HasMore()) {
		has = true;
		JsonModelPtr model = iter.PeekNextValue();
		json.append(model->JsonString() + ",");
		iter.MoveNext();
	}

	if(has) json.erase(json.length()-1);
	json.append("]");

	return SPtr(json);
}

void JsonModelStorage::LoadAll()
{
	LoadAllImpl();
}

JsonModelPtr JsonModelStorage::CreateImpl(const JsonObj& json)
{
	try
	{
		JsonModelPtr jmodel(new JsonModel(json));

		const char* id = json.getStringField(_fieldId.c_str());
		if(id == NULL) {
			FUGU_THROW(std::string("json string doesn't have id field('") + id+"')", 
						"JsonModelStorage::CreateImpl");
		}

		DBConnectionPtr conn = GetConnection();

		JsonModelMap::const_iterator iter;
		{
			boost::shared_lock<boost::shared_mutex> lock(_access);
			iter = _models.find(id);
		}

		if(iter == _models.end()) {
			// Model doesn't exists, creating new
			conn->insert(_ns, *jmodel);
		}
		else { // Model already exists, updating...
			conn->update(_ns, QUERY(_fieldId<<id), *jmodel);
		}

		{
			// Get upgradable access
			boost::upgrade_lock<boost::shared_mutex> lock(_access);
			// Get exclusive access
			boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
			// Now we have exclusive access

			_models.insert(std::make_pair<std::string, JsonModelPtr>(id, jmodel));
		}

		// Get error result from the last operation on this connection. 
		std::string error = conn->getLastError();
		if(!error.empty()) {
			FUGU_THROW(error, "JsonModelStorage::CreateImpl");
		}

		return jmodel;
	}
	catch(Exception& ex)
	{
		throw ex;
	}
	catch(mongo::DBException& ex)
	{
		FUGU_THROW(ex.toString(), "JsonModelStorage::CreateImpl");
	}
	catch(std::exception& ex)
	{
		FUGU_THROW(ex.what(), "JsonModelStorage::CreateImpl");
	}
}

void JsonModelStorage::LoadAllImpl(mongo::Query query)
{
	try
	{
		JsonModelMap fromdb;
		std::auto_ptr<mongo::DBClientCursor> cursor = GetConnection()->query(_ns, query);

		//getLastError();
		while(cursor->more()) {
			JsonObj json = cursor->next();
			const char* id = json.getStringField(_fieldId.c_str());

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
	catch(Exception& ex)
	{
		throw ex;
	}
	catch(mongo::DBException& ex)
	{
		FUGU_THROW(ex.toString(), "JsonModelStorage::LoadAll");
	}
	catch(std::exception& ex)
	{
		FUGU_THROW(ex.what(), "JsonModelStorage::LoadAll");
	}
}

}