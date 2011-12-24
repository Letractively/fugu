#include "viewdata.h"
#include "dbpool.h"
#include "exception.h"
#include <dbclient.h>

namespace fugu {

ViewData::~ViewData()
{
}

std::string ViewData::Name() const
{
	return _jsonObj.getStringField("Name");
}

std::string ViewData::Region() const
{
	return _jsonObj.getStringField("Region");
}

std::string ViewData::Content() const
{
	return _jsonObj.getStringField("Content");
}

std::string ViewData::JavaScript() const
{
	return _jsonObj.getStringField("JavaScript");
}

}