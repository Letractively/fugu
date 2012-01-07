#include "query.h"
#include "exception.h"
#include <string.h>

namespace fugu {

Query::Query()
{
}
Query::~Query()
{
}

QueryMethod Query::Type() const
{
	return _type;
}

const std::string& Query::Uri() const
{
	return _uri;
}

const std::string& Query::ViewName() const
{
	return _viewName;
}

const std::string Query::UserHash() const
{
	return _userHash;
}

const std::string Query::SessionHash() const
{
	return _sessionHash;
}

void  Query::SetType(QueryMethod type)
{
	_type = type;
}

void  Query::SetUri(const char* url, size_t len)
{
	_uri.assign(url, 0, len);
}

void Query::SetViewName(const char* viewName, size_t len)
{
	_viewName.assign(viewName, 0, len);
}

void  Query::SetUserHash(const char* buf, size_t len)
{
	_userHash.assign(buf, 0, len);
}

void  Query::SetSessionHash(const char* buf, size_t len)
{
	_sessionHash.assign(buf, 0, len);
}

const JsonObj& Query::Content() const
{
	return _content;
}

void Query::SetContent(const char* buf, size_t len)
{
	try
	{
		_content = mongo::fromjson(buf, (int*)&len);
	}
	catch(mongo::MsgAssertionException& ex)
	{
		FUGU_THROW(ex.what() ,"Query::SetContent");
	}
	catch(std::exception& ex)
	{
		FUGU_THROW(ex.what() ,"Query::SetContent");
	}
}

}