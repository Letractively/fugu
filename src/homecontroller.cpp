#include "homecontroller.h"
#include "response.h"
#include <sstream>

namespace fugu {

ResponsePtr HomeController::OKResponse()
{
	std::ostringstream contentstream;
	contentstream
	<< "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01//EN' 'http://www.w3.org/TR/html4/strict.dtd'>"
	<< "<html dir='ltr'>"
	<< "<head>"
	<< "<title>Fugu</title>"
	<< "<link rel='stylesheet' type='text/css' href='dojo/dijit/themes/tundra/tundra.css'/>"
	<< "<link rel='stylesheet' type='text/css' href='dojo/dojo/resources/dojo.css'/>"
	<< "<link rel='stylesheet' type='text/css' href='/om/site.css'/>"
	<< "<script type='text/javascript' src='dojo/dojo/dojo.js' djConfig='debug: true, parseOnLoad: true'></script>"
	<< "<script type='text/javascript' src='om/headerview.js'></script>"
	<< "<script type='text/javascript' src='om/menuview.js'></script>"
	<< "<script type='text/javascript' src='om/contentview.js'></script>"
	<< "<script type='text/javascript' src='om/appcontroller.js'></script>"
	<< "</head>"
	<< "<body class='tundra'>"
	<< "</body>"
	<< "</html>";

	std::string content =  contentstream.str();
	std::ostringstream response;
	response<<"HTTP/1.0 200 OK\r\n"
			<<"Location: www.google.com\r\n"
			<<"Content-Type: text/html; charset=UTF-8\r\n"
			<<"Content-Length: "<<content.length()<<"\r\n"
			<<"Set-Cookie: user=test"<<"\r\n"
			<<"Set-Cookie: session=test"<<"\r\n"
			<<"\r\n"<<content<<"\r\n";

	return new Response(response.str());
}

ResponsePtr HomeController::Get(QueryContextPtr ctx)
{
	return OKResponse();
}

Controller* HomeControllerFactory::CreateImpl(const std::string url)
{
	return new HomeController();
}

const std::string& HomeControllerFactory::ResourceUrl() const
{
	static std::string HOME_RESOURCE = "/home.fsp";
	return HOME_RESOURCE;
}

}