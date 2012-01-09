#ifndef __STRING_UTILS__
#define __STRING_UTILS__

#include "prerequisites.h"

namespace fugu {

StringPtr SPtr(const std::string& s);
StringPtr SPtr(const char* s);

}

#endif