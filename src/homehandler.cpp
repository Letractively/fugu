#include "homehandler.h"
//#include "reply.h"
//#include "query.h"
#include <sstream>

namespace fugu {

ReplyPtr HomeHandler::Process(ContextPtr ctx)
{
	std::ostringstream contentstream;
	contentstream
	<< "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01//EN' 'http://www.w3.org/TR/html4/strict.dtd'>"
	<< "<html dir='ltr'>"
	<< "<head>"
	<< "<title>Fugu</title>"
	<< "<link rel='stylesheet' type='text/css' href='dojo/dijit/themes/tundra/tundra.css'/>"
	<< "<link rel='stylesheet' type='text/css' href='dojo/dojo/resources/dojo.css'/>"
	<< "<link rel='stylesheet' type='text/css' href='/fugu/css/site.css'/>"
	<< "<script type='text/javascript' src='dojo/dojo/dojo.js' djConfig='debug: true, parseOnLoad: true'></script>"
	<< "<script type='text/javascript' src='fugu/headerview.js'></script>"
	<< "<script type='text/javascript' src='fugu/menuview.js'></script>"
	<< "<script type='text/javascript' src='fugu/contentview.js'></script>"
	<< "<script type='text/javascript' src='fugu/appcontroller.js'></script>"
	<< "</head>"
	<< "<body class='tundra'>"
	<< "</body>"
	<< "</html>";

	StringPtr ptr(new std::string(contentstream.rdbuf()->str()));
	return Html(ptr);
}

Handler* HomeHandlerFactory::CreateImpl()
{
	return new HomeHandler();
}

const std::string& HomeHandlerFactory::Name() const
{
	static std::string HOME_HANDLER_NAME = "homehandler";
	return HOME_HANDLER_NAME;
}

}