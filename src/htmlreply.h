#ifndef __FUGU_HTML_REPLY__
#define __FUGU_HTML_REPLY__

#include "reply.h"
#include <boost/noncopyable.hpp>

namespace fugu {

class HtmlReply : public Reply, private boost::noncopyable
{
public:
	HtmlReply(const std::string& html);
	virtual ~HtmlReply();
	bool Streamed() const;
	boost::asio::streambuf& StreamBuffer() const;
	const std::string& Response() const;
protected:
	std::string _html;
};

}

#endif