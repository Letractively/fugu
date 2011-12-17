#ifndef __FUGU_BASE_RESPONSE__
#define __FUGU_BASE_RESPONSE__

#include <string>
#include <streambuf>
#include <boost/asio.hpp>

namespace fugu {

class Reply
{
public:
	Reply();
	Reply(const std::string& data);
	virtual ~Reply();
	boost::asio::streambuf& StreamBuffer();

protected:
	std::ostream _stream;
	boost::asio::streambuf _streambuf;
};

}

#endif