#include "stringutils.h"

namespace fugu {

StringPtr SPtr(const std::string& s)
{
	return StringPtr(new std::string(s));
}

StringPtr SPtr(const char* s)
{
	return StringPtr(new std::string(s));
}

}