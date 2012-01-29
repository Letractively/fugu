#ifndef __FUGU_HANDLER_H__
#define __FUGU_HANDLER_H__

#include "prerequisites.h"
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace fugu {

class Handler : public boost::enable_shared_from_this<Handler>
{
friend class HandlerFactory;

typedef boost::function< void(HandlerPtr)> NotificationHandler;

public:
    Handler();
	virtual ~Handler();
	void Process(ContextPtr ctx);
	//bool LongRunning() const virtual = 0;
	RoutePtr Route() const;
	static ReplyPtr Error(std::exception& ex, bool critical);

protected:
    virtual void ProcessImpl(ContextPtr ctx)=0;
    // Single for session
    virtual bool Single();
    
	ReplyPtr Html(StringPtr html);
	ReplyPtr PartialView(JsonModelPtr view);
	ReplyPtr Json(StringPtr json);
    void InUse(bool state);
    bool InUse() const;
    
    void Return(ReplyPtr reply, ContextPtr ctx);
    void ReturnAndDestroy(ReplyPtr reply, ContextPtr ctx);
    
private:
    volatile bool _inUse;
    NotificationHandler OnDestroy;
	RoutePtr _route;
};

class HandlerFactory : private boost::noncopyable
{
protected:			
	virtual Handler* CreateImpl()=0;
    virtual void DoDestroy(Handler* handler)=0;
public:
	virtual const std::string& Name() const=0;
	virtual HandlerPtr Create(RoutePtr route);
	bool HasRights(UserPtr user);
};

}

#endif