#include "HttpHeader.h"

namespace fugu {

//HttpHeader EmptyHeader("", "");

HttpHeader::HttpHeader(const std::string& name, const std::string& value)
{
}

HttpHeader::~HttpHeader()
{
}

const std::string& HttpHeader::Name() const
{
	return _name;
}

const std::string& HttpHeader::Value() const
{
	return _value;
}

void HttpHeader::SetName(const std::string& name)
{
	_name = name;
}

void HttpHeader::SetValue(const std::string& value)
{
	_value = value;
}

}