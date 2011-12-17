#ifndef __FUGU_VIEW_FROM_DB_HANDLER_H__
#define __FUGU_VIEW_FROM_DB_HANDLER_H__

#include "handler.h"

namespace fugu {

class ViewFromDBHandler : public Handler
{
public:
	ReplyPtr Process(ContextPtr ctx);

private:
	ReplyPtr GetView(ContextPtr ctx);
	ReplyPtr UpdateView(ContextPtr ctx);
};

class ViewFromDBHandlerFactory : public HandlerFactory
{
protected:			
	Handler* CreateImpl();
public:
	const std::string& Name() const;

};

}

#endif