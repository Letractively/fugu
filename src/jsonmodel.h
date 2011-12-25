#ifndef __FUGU_JSON_MODEL__
#define __FUGU_JSON_MODEL__

#include "prerequisites.h"
#include "iterators.h"
#include <map>
#include <dbclient.h>
#include <boost/thread/shared_mutex.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace fugu {

class JsonModel //: public boost::enable_shared_from_this<JsonModel>,
					//private boost::noncopyable
{
public:
	JsonModel(const JsonObj& obj);
	virtual ~JsonModel();
	std::string JsonString() const;
	const JsonObj& JsonObject() const;

	template<typename T>
	boost::shared_ptr<T> As()
	{
		return boost::shared_ptr<T>(this);
	}

protected:
	JsonObj _jsonObj;
};


typedef std::map<std::string, JsonModelPtr> JsonModelMap;
typedef ConstMapIterator<JsonModelMap> JsonModelMapIterator;

// In memeoty sorage
class JsonModelCache
{
public:
	// ns - db table name
	JsonModelCache(const std::string& ns, const std::string& idFieldName);
	virtual ~JsonModelCache();

	// Creates new model by json string, and add it to the database, or update existing
	JsonModelPtr Create(const std::string& json);
	// Gets model by id
	JsonModelPtr GetById(const std::string& id) const;
	// Gets all models
	JsonModelMapIterator All();
	// Gets all models in json format
	// toReplace - data should be replaced, as example: passwords before sending to client
	StringPtr AllAsJson(const std::string& toReplace="");

protected:
	virtual JsonModelPtr CreateImpl(const std::string& json);
	virtual void LoadAll();

protected:
	std::string _ns;
	std::string _idFieldName;
	JsonModelMap _models;
	mutable boost::shared_mutex _access;
};

//typedef std::vector<JsonModelPtr> JsonModelList;
//typedef VectorIterator<JsonModelList> JsonModelListIterator;

}

#endif