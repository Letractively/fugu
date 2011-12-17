#ifndef __FUGU_HANDLER_H__
#define __FUGU_HANDLER_H__

#include "prerequisites.h"
#include <vector>
#include <map>

namespace fugu {

class Handler
{
friend class HandlerFactory;

public:
	virtual ~Handler();
	virtual ReplyPtr Process(ContextPtr ctx)=0;
	//bool LongRunning() const virtual = 0;
	RoutePtr Route() const;

protected:
	ReplyPtr View(const std::string& html);
	ReplyPtr PartialView(const JsonObj& json);
	ReplyPtr PartialView(const std::string& json);
	ReplyPtr Json(const std::string& json);
	ReplyPtr Json(const JsonObj& json);

private:
	RoutePtr _route;
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