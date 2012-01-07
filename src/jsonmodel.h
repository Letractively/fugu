#ifndef __FUGU_JSON_MODEL__
#define __FUGU_JSON_MODEL__

#include "prerequisites.h"
#include "iterators.h"
#include <dbclient.h>
#include <boost/thread/shared_mutex.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace fugu {

class JsonModel : public JsonObj
{
public:
	JsonModel();
	explicit JsonModel(const JsonObj& obj);
	virtual ~JsonModel();
	std::string JsonString() const;

	template<typename T>
	T* As()
	{
		return static_cast<T*>(this);
	}
};

typedef std::map<std::string, JsonModelPtr> JsonModelMap;
typedef ConstMapIterator<JsonModelMap> JsonModelMapIterator;

// In memory sorage
class JsonModelStorage
{
public:
	// ns - db table name
	JsonModelStorage(const std::string& ns, const std::string& idFieldName);
	virtual ~JsonModelStorage();

	// Creates new model by json object, and add it to the database, or update existing
	JsonModelPtr Create(const JsonObj& jsonObj);
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
	virtual JsonModelPtr CreateImpl(const JsonObj& json);
	virtual void LoadAll();

protected:
	std::string _ns;
	std::string _idFieldName;
	JsonModelMap _models;
	mutable boost::shared_mutex _access;
};

}

#endif