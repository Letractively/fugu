#ifndef __FUGU_HANDLER_INFO_H__
#define __FUGU_HANDLER_INFO_H__

#include "prerequisites.h"

namespace fugu {

class Route : private boost::noncopyable
{
public:
	Route(const std::string& handlerName, const std::string& viewName)
		:_handlerName(handlerName)
		,_viewName(viewName){}

	const std::string& HandlerName() const { return _handlerName; }
	const std::string& ViewName() const { return _viewName; }

private:
	std::string _handlerName;
	std::string _viewName;
};

}

#endif