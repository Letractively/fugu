#ifndef __FUGU_QUERY__
#define __FUGU_QUERY__

#include "prerequisites.h"

namespace fugu {

class JsonObj {};

enum QueryMethod { 
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
	QueryMethod Type() const;
	// Returns request URL
	const std::string& Uri() const;
	// Returns request view name
	const std::string& ViewName() const;
	bool HasView() const;
	// Returns user hash
	const std::string UserHash() const;
	// Returns session hash
	const std::string SessionHash() const;
	// Returns query content
	const JsonObj& Content() const;
	bool ClearCache() const;

private: 
	// Sets query type
	void SetType(QueryMethod type);
	// Sets query url
	void SetUri(const char* buf, size_t len);
	// Sets query url
	void SetViewName(const char* buf, size_t len);
	// Sets user hash
	void SetUserHash(const char* buf, size_t len);
	// Sets session hash
	void SetSessionHash(const char* buf, size_t len);
	// Sets json content
	void SetContent(const char* buf, size_t len);
	void ClearCache(bool clear = true);

private:
	QueryMethod _type;
	std::string _uri;
	std::string _viewName;
	std::string _userHash;
	std::string _sessionHash;
	JsonObj _content;
	bool _clearCache;
};

}

#endif