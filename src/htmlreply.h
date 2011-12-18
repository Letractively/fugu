#ifndef __FUGU_HTML_REPLY__
#define __FUGU_HTML_REPLY__

#include "reply.h"

namespace fugu {

class HtmlReply : public Reply, private boost::noncopyable
{
public:
	HtmlReply(StringPtr html);
	virtual ~HtmlReply();
	bool Streamed() const;
	boost::asio::streambuf& ResponseStream() const;
	const std::string& Response() const;

protected:
	StringPtr _html;
	mutable boost::asio::streambuf _streambuf;
	mutable std::ostream _stream;
};

}

#endif