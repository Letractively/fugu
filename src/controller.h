#ifndef __FUGU_CONTROLER_H__
#define __FUGU_CONTROLER_H__

#include "prerequisites.h"
#include <vector>
#include <map>

namespace fugu {

class Controller : private boost::noncopyable
{
friend class ControllerFactory;

public:
	Controller();
	virtual ~Controller();
	virtual ResponsePtr Get(QueryContextPtr ctx);
	virtual ResponsePtr Put(QueryContextPtr ctx);
	virtual ResponsePtr Delete(QueryContextPtr ctx);
	virtual ResponsePtr Post(QueryContextPtr ctx);
	const std::string ResourceUrl() const { return _resourceUrl; }

protected:
	ResponsePtr View();
	ResponsePtr PartialView();
	ResponsePtr Json(const std::string json);
	ResponsePtr Xml(const std::string json);

private:
	std::string _resourceUrl;
};

class ControllerFactory : private boost::noncopyable
{
protected:			
	virtual Controller* CreateImpl(const std::string url)=0;
public:
	virtual const std::string& ResourceUrl() const=0;
	virtual ControllerPtr Create(const std::string url);
	bool HasRights(UserPtr user);
};

}

#endif