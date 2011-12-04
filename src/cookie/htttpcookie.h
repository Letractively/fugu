#ifndef __FUGU_HTTP_COOKIE_H__
#define __FUGU_HTTP_COOKIE_H__

#include "prerequisites.h"

namespace fugu {

class HttpCookie : private boost::noncopyable
{
public:
	HttpCookie(const std::string& name, const std::string& value);
	const std::string& Name() const;
	const std::string& Value() const;
	const std::string& Comment() const;
	const std::string& Domain() const;
	const std::string& Path() const;
	bool Secure() const;
	int MaxAge() const;

private:
	friend std::ostream &operator << (std::ostream &, HttpCookie const &);
	void WriteToStream(std::ostream &) const;	

private:
	std::string _name;
	std::string _value;
	std::string _comment;
	// Storage time. expires=Monday, DD-Mon-YYYY HH:MM:SS GM
	std::string _expires;
	std::string _domain;
	std::string _path;
	bool _secure;
	bool _hasAge;
	boost::uint16_t _maxAge;

};

typedef std::map<std::string, std::string> HttpCookies;
typedef MapIterator<HttpCookies> HttpCookiesIterator;

}

#endif