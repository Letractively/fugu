#ifndef __FUGU_HANDLER_H__
#define __FUGU_HANDLER_H__

#include "prerequisites.h"

namespace fugu {

class Handler
{
friend class HandlerFactory;

public:
	virtual ~Handler();
	virtual ReplyPtr Process(ContextPtr ctx)=0;
	//bool LongRunning() const virtual = 0;
	RoutePtr Route() const;
	static ReplyPtr Error(std::exception& ex, bool critical);

protected:
	ReplyPtr Html(StringPtr html);
	ReplyPtr PartialView(JsonModelPtr view);
	ReplyPtr Json(const std::string& json);

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