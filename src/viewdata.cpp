#include "viewdata.h"
#include "exception.h"

namespace fugu {

ViewData::~ViewData()
{
}

std::string ViewData::Name() const
{
	return getStringField("Name");
}

std::string ViewData::Content() const
{
	return getStringField("Content");
}

std::string ViewData::JavaScript() const
{
	return getStringField("JavaScript");
}

}