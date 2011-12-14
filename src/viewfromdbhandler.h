#ifndef __FUGU_VIEW_FROM_DB_HANDLER_H__
#define __FUGU_VIEW_FROM_DB_HANDLER_H__

#include "Handler.h"

namespace fugu {

class ViewFromDBHandler : public Handler
{
public:
	ResponsePtr Process(ContextPtr ctx);

private:
	ResponsePtr GetView(ContextPtr ctx);
	ResponsePtr UpdateView(ContextPtr ctx);
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