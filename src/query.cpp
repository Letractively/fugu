#include "query.h"
#include "logger.h"
namespace fugu {

Query::Query()
{
}
Query::~Query()
{
}
// Returns query type
QueryType Query::Type() const
{
	return _type;
}
// Returns request URL
const std::string& Query::Url() const
{
	return _url;
}
// Returns user hash
const std::string Query::UserHash() const
{
	return _userHash;
}
// Returns session hash
const std::string Query::SessionHash() const
{
	return _sessionHash;
}
// Sets query type
void  Query::SetType(QueryType type)
{
	_type = type;
}
// Sets query url
void  Query::SetUrl(const char* buf, size_t len)
{
	_url.assign(buf, 0, len);
}
// Sets user hash
void  Query::SetUserHash(const char* buf, size_t len)
{
	_userHash.assign(buf, 0, len);
}
// Sets session hash
void  Query::SetSessionHash(const char* buf, size_t len)
{
	_sessionHash.assign(buf, 0, len);
}
// Returns query content
const JsonObj& Query::Content() const
{
	return _content;
}
// Sets json content
void Query::SetContent(const char* buf, size_t len)
{
	try
	{
		_content = mongo::fromjson(buf, (int*)&len);
	}
	catch(std::exception& ex)
	{
		Log(ex.what());
	}
}

}