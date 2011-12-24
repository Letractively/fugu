#ifndef __FUGU_VIEW_DATA__
#define __FUGU_VIEW_DATA__

#include "jsonmodel.h"

namespace fugu {

class ViewData : public JsonModel, : private boost::noncopyable
{
public:
	virtual ~ViewData();
	std::string Name() const;
	std::string Region() const;
	std::string Content() const;
	std::string JavaScript() const;
};

}

#endif