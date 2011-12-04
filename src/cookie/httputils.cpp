#include "httputils.h"

namespace fugu {
namespace utils {

bool IsChar(int c)
{
	return c >= 0 && c <= 127;
}

bool IsCtl(int c)
{
	return (c >= 0 && c <= 31) || (c == 127);
}

bool IsTspecial(int c)
{
	switch (c)
	{
		case '(': case ')': case '<': case '>': case '@':
		case ',': case ';': case ':': case '\\': case '"':
		case '/': case '[': case ']': case '?': case '=':
		case '{': case '}': case ' ': case '\t':
		return true;
		default:
		return false;
	}
}

bool IsDigit(int c)
{
	return c >= '0' && c <= '9';
}

bool HasQuotes(const std::string& input)
{
	std::string::const_iterator begin = input.begin();
	std::string::const_iterator end = input.end();

	char c;
	while(begin < end && 0x20<=(c=*begin) && c<=0x7E && !IsTspecial(c))
		begin++;

	return input.end() == begin;
}

std::string EscapeQuote(const std::string& input)
{
	std::string result;
	result.reserve(input.size());
	result+='"';
	for(std::string::const_iterator p=input.begin();p!=input.end();++p) 
	{
		char c=*p;
		if(0<=c && c<' ') {
			result+='\\';
		}
		result+=c;
	}
	result+='"';
	return result;
}

std::string Unquote(const std::string& input)
{
		std::string::const_iterator p, begin;
		p = begin = input.begin();
		std::string::const_iterator end = input.end();

		std::string result;
		if(p>=end || *p!='\"')
			return result;
		result.reserve(end-p);
		p++;
		while(p < end) {
			char c=*p++;
			if(c=='\"') {
				begin=p;
				return result;
			}
			else if(c=='\\' && p<end)
				result+= *p++;
			else
				result+=c;
		}
		result.clear();
		return result;
}

bool HexDigit(int c) 
{ 
	return ('0'<=c && c<='9') || ('a'<=c && c<='f') || ('A'<=c && c<='F'); 
}

}
}