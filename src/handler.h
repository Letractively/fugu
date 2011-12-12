#ifndef __FUGU_CONTROLER_H__
#define __FUGU_CONTROLER_H__

#include "prerequisites.h"
#include <vector>
#include <map>

namespace fugu {

class Handler : private boost::noncopyable
{
friend class HandlerFactory;

public:
	Handler();
	virtual ~Handler();
	virtual ResponsePtr Get(ContextPtr ctx);
	virtual ResponsePtr Put(ContextPtr ctx);
	virtual ResponsePtr Delete(ContextPtr ctx);
	virtual ResponsePtr Post(ContextPtr ctx);
	const std::string ResourceUrl() const { return _resourceUrl; }

protected:
	ResponsePtr View();
	ResponsePtr PartialView();
	ResponsePtr Json(const std::string json);
	ResponsePtr Xml(const std::string json);

private:
	std::string _resourceUrl;
};

class HandlerFactory : private boost::noncopyable
{
protected:			
	virtual Handler* CreateImpl(const std::string url)=0;
public:
	virtual const std::string& ResourceUrl() const=0;
	virtual HandlerPtr Create(const std::string url);
	bool HasRights(UserPtr user);
};

}

#endif