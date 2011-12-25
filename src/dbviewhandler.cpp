#include "dbviewhandler.h"
#include "jsonreply.h"
#include "query.h"
#include "viewdata.h"
#include "context.h"
#include "exception.h"
#include <sstream>

namespace fugu {

ReplyPtr DBViewHandler::Process(ContextPtr ctx)
{
	const std::string& url = ctx->Query()->Url();

	if(url.compare("/fugu/getview.fsp") == 0) {
		return GetView(ctx);
	}
	else if(url.compare("/fugu/getallviews.fsp") == 0) {
		return GetAllViews(ctx); 
	}
	else if(url.compare("/fugu/saveview.fsp") == 0) {
		return UpdateView(ctx);
	}

	FUGU_THROW("Unknown url:'" + url + "'", "DBViewHandler::Process");
}

ReplyPtr DBViewHandler::GetAllViews(ContextPtr ctx)
{
	try
	{
		JsonReplyPtr reply(new JsonReply());

		JsonModelCache mgr("test.fugu.views", "Name");
		JsonModelMapIterator viewsIter = mgr.All();
		std::string json = "[";
		bool has = false;
		while(viewsIter.HasMore()) {
			has = true;
			JsonModelPtr view = viewsIter.PeekNextValue();
			json.append(view->JsonString() + ",");
			viewsIter.MoveNext();
		}

		if(has) json.erase(json.length()-1);
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
		return Handler::Error(FUGU_EXCEPT(e.what() ,"DBViewHandler::GetAllViews"), true);
	}
}

ReplyPtr DBViewHandler::GetView(ContextPtr ctx)
{
	return ReplyPtr();
}

ReplyPtr DBViewHandler::UpdateView(ContextPtr ctx)
{
	JsonModelCache mgr("test.fugu.views", "Name");
	mgr.Create(ctx->Query()->Content());
	return GetAllViews(ctx);
}

Handler* DBViewHandlerFactory::CreateImpl()
{
	return new DBViewHandler;
}

const std::string& DBViewHandlerFactory::Name() const
{
	const static std::string VIEW_FROM_DB_HANDLER = "dbviewhandler";
	return VIEW_FROM_DB_HANDLER;
}

}