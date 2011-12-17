#ifndef __FUGU_REPLY__
#define __FUGU_REPLY__

#include <string>
#include <streambuf>
#include <boost/asio.hpp>

namespace fugu {

class Reply
{
public:
	virtual ~Reply();
	virtual bool Streamed() const =0;
	virtual boost::asio::streambuf& ResponseStream() const;
	virtual const std::string& Response() const;
protected:
	static boost::asio::streambuf& EmptyResponseStream();
	static const std::string& EmptyResponse();
};

}

#endif