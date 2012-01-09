#ifndef __FUGU_TEMPLATE_PAGE_HANDLER_H__
#define __FUGU_TEMPLATE_PAGE_HANDLER_H__

#include "handler.h"

namespace fugu {

class TempaltePageHandler : public Handler, private boost::noncopyable
{
public:
	ReplyPtr Process(ContextPtr ctx);

private:
	ViewDataPtr _pagetemplate;
};

class TempaltePageHandlerFactory : public HandlerFactory
{
protected:			
	Handler* CreateImpl();
public:
	const std::string& Name() const;

};

}

#endif