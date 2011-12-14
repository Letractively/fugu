#include "viewfromdbhandler.h"
#include "response.h"
#include "viewdata.h"
#include "context.h"
#include "httprequest.h"
#include <sstream>

namespace fugu {

ResponsePtr ViewFromDBHandler::Process(ContextPtr ctx)
{
	switch(ctx->Request()->Method())
	{
		case HttpMethods::HTTP_PUT:
			return UpdateView(ctx);
			break;
		case HttpMethods::HTTP_GET:
		case HttpMethods::HTTP_POST:
			return GetView(ctx);
			break;
	};
}
	
ResponsePtr ViewFromDBHandler::GetView(ContextPtr ctx)
{
	ViewDataManager mgr;
	//ViewPtr view = mgr.CreateView(ctx->Request()->Content());
	std::string content =  "<html><head><title>ping</title></head><body><h1>fugu service is running...</h1></body></html>";
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

ResponsePtr ViewFromDBHandler::UpdateView(ContextPtr ctx)
{
	ViewDataManager mgr;
	mgr.CreateView(ctx->Request()->Content());
	std::string content =  "<html><head><title>ping</title></head><body><h1>fugu service is running...</h1></body></html>";
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