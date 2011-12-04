#include "requesthrouter.h"
#include "HttpResponse.h"
#include "httprequest.h"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>

namespace fugu {

RequestRouter::RequestRouter(const std::string& root)
  : _root(root)
{
}

void RequestRouter::Route(const HttpRequest& req, HttpResponse& rep)
{
	//// Decode url to path.
	//std::string _requestpath;
	//if (!UrlDecode(req.uri, _requestpath))
	//{
	//	//TODP: rep = Reply::stock_reply(Reply::bad_request);
	//	return;
	//}

	//// Request path must be absolute and not contain "..".
	//if (_requestpath.empty() || _requestpath[0] != '/' || _requestpath.find("..") != std::string::npos)
	//{
	//	//TODO: rep = Reply::stock_reply(Reply::bad_request);
	//	return;
	//}

	//// Open the file to send back.
	//std::string full_path = _root + _requestpath;
	//std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
	//if (!is)
	//{
	//	//TODO: rep = Reply::stock_reply(Reply::not_found);
	//	return;
	//}

	//// Fill out the reply to be sent to the client.
	//rep.status = Reply::ok;
	//char buf[512];
	//while (is.read(buf, sizeof(buf)).gcount() > 0)
	//rep.content.append(buf, is.gcount());
	//rep.headers.resize(2);
	//rep.headers[0].name = "Content-Length";
	//rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
	//rep.headers[1].name = "Content-Type";
	//rep.headers[1].value = "text/plain";
}

bool RequestRouter::UrlDecode(const std::string& in, std::string& out)
{
	out.clear();
	out.reserve(in.size());
	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (in[i] == '%')
		{
			if (i + 3 <= in.size())
			{
				int value = 0;
				std::istringstream is(in.substr(i + 1, 2));
				if (is >> std::hex >> value)
				{
					out += static_cast<char>(value);
					i += 2;
				}
				else return false;
			}
			else return false;
		}
		else if (in[i] == '+') out += ' ';
		else out += in[i];
	}
	return true;
}
}