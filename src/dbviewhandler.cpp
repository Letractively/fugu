#include "dbviewhandler.h"
#include "jsonreply.h"
#include "query.h"
#include "viewdata.h"
#include "context.h"
#include "exception.h"
#include <sstream>

namespace fugu {

ReplyPtr ViewFromDBHandler::Process(ContextPtr ctx)
{

	//JsonReply* reply = new JsonReply();
	//reply->SetError("Test error", false);
	/*
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
	*/

	return GetViewsList(ctx);
}
	
ReplyPtr ViewFromDBHandler::GetViewsList(ContextPtr ctx)
{
	try
	{
		JsonReply* reply = new JsonReply();

		JsonModelCache mgr("test.fugu.views", "Name");
		JsonModelMapIterator viewsIter = mgr.All();
		std::string json = "[";
		bool has = false;
		while(viewsIter.HasMore()) {
			has = true;
			JsonModelPtr view = viewsIter.PeekNextValue();
			ViewData* v = (ViewData*)view.get();
			json.append("{\"Name\":\"" +  v->Name() + "\"},");
			viewsIter.MoveNext();
		}

		if(has)
			json.erase(json.length()-1);

		json.append("]");

		reply->SetJson(json);

		return reply;
	}
	catch(Exception& fe)
	{
		return Handler::Error(fe, true);
	}
	catch(std::exception& e)
	{
		return Handler::Error(FUGU_EXCEPT(e.what() ,"ViewFromDBHandler::GetViewsList"), true);
	}
}

ReplyPtr ViewFromDBHandler::GetView(ContextPtr ctx)
{
	//ViewDataManager mgr;
	////ViewPtr view = mgr.CreateView(ctx->Request()->Content());
	//std::string content =  "<html><head><title>ping</title></head><body><h1>fugu service is running...</h1></body></html>";
	//std::ostringstream response;
	//response<<"HTTP/1.0 200 OK\r\n"
	//		<<"Location: www.google.com\r\n"
	//		<<"Content-Type: text/html; charset=UTF-8\r\n"
	//		<<"Content-Length: "<<content.length()<<"\r\n"
	//		<<"Set-Cookie: user=test"<<"\r\n"
	//		<<"Set-Cookie: session=test"<<"\r\n"
	//		<<"\r\n"<<content<<"\r\n";

	//return new Response(response.str());
	return NULL;
}

ReplyPtr ViewFromDBHandler::UpdateView(ContextPtr ctx)
{
	//ViewDataManager mgr;
	//mgr.CreateView(ctx->Request()->Content());
	//std::string content =  "<html><head><title>ping</title></head><body><h1>fugu service is running...</h1></body></html>";
	//std::ostringstream response;
	//response<<"HTTP/1.0 200 OK\r\n"
	//		<<"Location: www.google.com\r\n"
	//		<<"Content-Type: text/html; charset=UTF-8\r\n"
	//		<<"Content-Length: "<<content.length()<<"\r\n"
	//		<<"Set-Cookie: user=test"<<"\r\n"
	//		<<"Set-Cookie: session=test"<<"\r\n"
	//		<<"\r\n"<<content<<"\r\n";

	//return new Response(response.str());

	return NULL;
}

Handler* ViewFromDBHandlerFactory::CreateImpl()
{
	return new ViewFromDBHandler;
}

const std::string& ViewFromDBHandlerFactory::Name() const
{
	const static std::string VIEW_FROM_DB_HANDLER = "dbviewhandler";
	return VIEW_FROM_DB_HANDLER;
}

}