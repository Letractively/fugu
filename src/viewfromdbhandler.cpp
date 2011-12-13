#include "viewfromdbhandler.h"
#include "response.h"
#include <sstream>

namespace fugu {

ResponsePtr ViewFromDBHandler::Process(ContextPtr ctx)
{
	std::string content =  "<html><head><title>ping</title></head><body><h1>db from view</h1></body></html>";
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
	
Handler* ViewFromDBHandlerFactory::CreateImpl()
{
	return new ViewFromDBHandler;
}

const std::string& ViewFromDBHandlerFactory::Name() const
{
	const static std::string VIEW_FROM_DB_HANDLER = "viewfromdbhandler";
	return VIEW_FROM_DB_HANDLER;
}

}