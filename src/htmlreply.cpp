#include "htmlreply.h"

namespace fugu {

HtmlReply::HtmlReply(StringPtr html)
	:Reply(HTTP_REPLY)
	,_stream(&_streambuf)
	,_html(html)
{
}

HtmlReply::~HtmlReply()
{
}

bool HtmlReply::Streamed() const
{
	return true;
}

boost::asio::streambuf& HtmlReply::ResponseStream() const
{
	_stream << "HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n Content-Length: "
			<< _html->size() << "\r\n";

	StringPtr headers = Reply::Headers();
	if(headers && !headers->empty())
		_stream << *headers;

	_stream << "\r\n" << *_html;

	return _streambuf;
}

const std::string& HtmlReply::Response() const
{
	return *_html;
}

}