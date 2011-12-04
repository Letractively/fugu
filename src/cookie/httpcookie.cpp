#include "htttpcookie.h"
#include "httputils.h"
#include <exception>
#include <boost/lexical_cast.hpp>

namespace fugu {

HttpCookie::HttpCookie(const std::string& name, const std::string& value)
	:_name(name)
	,_value(value)
{
}

const std::string& HttpCookie::Name() const
{
	return _name;
}

const std::string& HttpCookie::Value() const
{
	return _value;
}

const std::string& HttpCookie::Comment() const
{
	return _comment;
}

const std::string& HttpCookie::Domain() const
{
	return _domain;
}

const std::string& HttpCookie::Path() const
{
	return _path;
}

bool HttpCookie::Secure() const
{
	return _secure;
}

int HttpCookie::MaxAge() const
{
	return _maxAge;
}

void HttpCookie::WriteToStream(std::ostream &out) const
{
	if(_name.empty())
		throw std::exception("Cookie's name is not defined");

	out << "Set-Cookie:" << _name << '=';

	if(utils::HasQuotes(_value))
		out << _value;
	else
		out <<  utils::EscapeQuote(_value);

	if(!_comment.empty())
		out << "; Comment=" << utils::EscapeQuote(_comment);

	if(!_domain.empty())
		out<<"; Domain=" << _domain;

	if(_hasAge)
		out << "; Max-Age=" << boost::lexical_cast<std::string>(_maxAge);

	if(_path.empty())
		out << "; Path=" << _path;

	if(_secure)
		out << "; Secure";

	out << "; Version=1";
}

std::ostream &operator<<(std::ostream &out, HttpCookie const &cookie)
{
	cookie.WriteToStream(out);
	return out;
}


}