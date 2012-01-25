#ifndef __FUGU_JSON_MODEL__
#define __FUGU_JSON_MODEL__

#include "prerequisites.h"
#include "iterators.h"
#include <boost/thread/shared_mutex.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>

namespace fugu {

class JsonModel
{
public:
	JsonModel();
	virtual ~JsonModel();
	std::string JsonString() const;
	StringPtr JsonStringPtr() const;

	template<typename T>
	T* As()
	{
		return static_cast<T*>(this);
	}
};

typedef std::map<std::string, JsonModelPtr> JsonModelMap;
typedef ConstMapIterator<JsonModelMap> JsonModelMapIterator;

class DBConnectionPtr
{
};

// In memory sorage
class JsonModelStorage
{
public:
	typedef boost::function< DBConnectionPtr()> GetConnectionHandler;

	// ns - db table name space
	JsonModelStorage(const std::string& ns, const std::string& idFieldName, GetConnectionHandler getconn);
	virtual ~JsonModelStorage();

	// Creates new model by json string, and add it to the database, or update existing
	JsonModelPtr Create(const std::string& json);
	// Gets model by id
	JsonModelPtr GetById(const std::string& id) const;
	void Delete(const std::string& id);
	// Gets all models
	JsonModelMapIterator All();
	// Gets all models in json format
	// toReplace - data should be replaced, as example: passwords before sending to client
	StringPtr AllAsJson();
	void LoadAll();

protected:
	//virtual JsonModelPtr CreateImpl(const JsonObj& json);
	virtual void LoadAllImpl();

protected:
	std::string _ns;
	std::string _fieldId;
	JsonModelMap _models;
	mutable boost::shared_mutex _access;
	GetConnectionHandler GetConnection;
};

}

#endif