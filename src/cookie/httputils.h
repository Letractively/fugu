#ifndef __FUGU_HTTP_UTILS__
#define __FUGU_HTTP_UTILS__

#include <string>

namespace fugu {
namespace utils {

// Check if a byte is an HTTP character.
bool IsChar(int c);
// Check if a byte is an HTTP control character.
bool IsCtl(int c);
// Check if a byte is defined as an HTTP tspecial character.
bool IsTspecial(int c);
// Check if a byte is a digit.
bool IsDigit(int c);
bool HasQuotes(const std::string& input);
std::string EscapeQuote(const std::string& input);
std::string Unquote(const std::string& input);
bool HexDigit(int c);

}
}

#endif