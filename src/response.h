#ifndef __FUGU_BASE_RESPONSE__
#define __FUGU_BASE_RESPONSE__

#include <string>
#include <streambuf>
#include <boost/asio.hpp>

namespace fugu {

class Response
{
public:
	Response(const std::string data);
	Response();
	virtual ~Response();
	boost::asio::streambuf& StreamBuffer();

protected:
	std::ostream _stream;
	boost::asio::streambuf _streambuf;
};

}

#endif