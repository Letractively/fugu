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