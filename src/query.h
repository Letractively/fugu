#ifndef __FUGU_QUERY__
#define __FUGU_QUERY__

#include "prerequisites.h"
#include <string>
#include <dbclient.h>

namespace fugu {

enum QueryType { 
	QUERY_DELETE	= 0,
	QUERY_GET,
	QUERY_POST,
	QUERY_PUT,
	QUERY_WEBSOCKET,
	NOT_SUPPORTED
};

// A request received from a client.
class Query : private boost::noncopyable
{
friend class HttpParser;
public:
	// Default constuctor
	Query();
	virtual ~Query();

	// Returns query type
	QueryType Type() const;
	// Returns request URL
	const std::string& Url() const;
	// Returns user hash
	const std::string UserHash() const;
	// Returns session hash
	const std::string SessionHash() const;
	// Returns query content
	const JsonObj& Content() const;
private:
	// Sets query type
	void SetType(QueryType type);
	// Sets query url
	void SetUrl(const char* buf, size_t len);
	// Sets user hash
	void SetUserHash(const char* buf, size_t len);
	// Sets session hash
	void SetSessionHash(const char* buf, size_t len);
	// Sets json content
	void SetContent(const char* buf, size_t len);

private:
	QueryType _type;
	std::string _url;
	std::string _userHash;
	std::string _sessionHash;
	JsonObj _content;
};

}

#endif