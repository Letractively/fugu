#ifndef __FUGU_HANDLER_H__
#define __FUGU_HANDLER_H__

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
	virtual ResponsePtr Process(ContextPtr ctx)=0;
	//bool LongRunning() const virtual = 0;
	const std::string Name() const { return _name; }
	const std::string ViewName() const { return _viewName; }

protected:
	ResponsePtr View();
	ResponsePtr PartialView();
	ResponsePtr Json(const std::string json);
	ResponsePtr Xml(const std::string json);

private:
	std::string _name;
	std::string _viewName;
};

class HandlerFactory : private boost::noncopyable
{
protected:			
	virtual Handler* CreateImpl()=0;
public:
	virtual const std::string& Name() const=0;
	virtual HandlerPtr Create(RoutePtr route);
	bool HasRights(UserPtr user);
};

}

#endif