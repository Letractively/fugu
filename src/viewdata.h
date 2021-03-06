#ifndef __FUGU_VIEW_DATA__
#define __FUGU_VIEW_DATA__

#include "jsonmodel.h"

namespace fugu {

class ViewData : public JsonModel
{
public:
	virtual ~ViewData();
	std::string Name() const;
	std::string Content() const;
	std::string JavaScript() const;
};

class ViewDataStorage : public JsonModelStorage
{
public:
	ViewDataStorage(const std::string& ns);
	~ViewDataStorage();

protected:
	virtual JsonModelPtr CreateImpl(const JsonObj& json);
	virtual void LoadAll(mongo::Query query = mongo::Query());
};

}

#endif