#ifndef __FUGU_HTTP_HEADER__
#define __FUGU_HTTP_HEADER__

#include "prerequisites.h"

namespace fugu {

class HttpHeader : private boost::noncopyable
{
public:
	HttpHeader(const std::string& name, const std::string& value);
	virtual ~HttpHeader();
	const std::string& Name() const;
	const std::string& Value() const;
	void SetName(const std::string& name);
	void SetValue(const std::string& value);

protected:
	std::string _name;
	std::string _value;
};

typedef std::map<std::string, std::string> HttpHeaders;
typedef ConstMapIterator<HttpHeaders> HttpHeadersIterator;

}

#endif