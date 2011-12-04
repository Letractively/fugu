#include "logger.h"
#include <iostream>

namespace fugu {

void Log(const std::string& entry)
{
	std::cout << entry << std::endl;
}

}