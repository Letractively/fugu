#include "htmlreply.h"

namespace fugu {

HtmlReply::HtmlReply(const std::string& html)
	:_html(html)
{
}

HtmlReply::~HtmlReply()
{
}

bool HtmlReply::Streamed() const
{
	return false;
}

const std::string& HtmlReply::Response() const
{
	return _html;
}


}