#include "dbviewhandler.h"
#include "config.h"
#include "context.h"
#include "database.h"
#include "jsonreply.h"
#include "query.h"
#include "viewdata.h"
#include "exception.h"
#include <sstream>

namespace fugu {

ReplyPtr DBViewHandler::Process(ContextPtr ctx)
{
	const std::string& url = ctx->Query()->Uri();

	if(url.compare("/") == 0 || url.empty())
		return GetPage(ctx);

	if(url.compare("/getview") == 0)
		return GetView(ctx);

	if(url.compare("/getallviews") == 0)
		return GetAllViews(ctx);

	if(url.compare("/saveview") == 0) {
		return UpdateView(ctx);
	}

	FUGU_THROW("Unknown url:'" + url + "'", "DBViewHandler::Process");
}

ReplyPtr DBViewHandler::GetPage(ContextPtr ctx)
{
	JsonModelPtr view = ctx->Db()->Views()->GetById(ctx->Cfg()->PageTemplate());
	StringPtr page(new std::string(view->getStringField("Content")));
	return Html(page);
}

ReplyPtr DBViewHandler::GetAllViews(ContextPtr ctx)
{
	try
	{
		JsonReplyPtr reply(new JsonReply());


		JsonModelMapIterator viewsIter = ctx->Db()->Views()->All();
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
	try
	{
		JsonModelPtr view = ctx->Db()->Views()->GetById(ctx->Query()->Content().getStringField("ViewName"));
		return PartialView(view);
	}
	catch(Exception& fe)
	{
		return Handler::Error(fe, true);
	}
	catch(std::exception& e)
	{
		return Handler::Error(FUGU_EXCEPT(e.what() ,"DBViewHandler::GetView"), true);
	}
}

ReplyPtr DBViewHandler::UpdateView(ContextPtr ctx)
{
	try
	{
		if(ctx->Query()->Content().firstElement().isABSONObj())
		{
			mongo::BSONObjIterator iter = ctx->Query()->Content();
			while(iter.more())
			{
				mongo::BSONElement el = iter.next();
				mongo::BSONObj view;
				el.Val(view);
				ctx->Db()->Views()->Create(view);
			}
		}
		else
		{
			ctx->Db()->Views()->Create(ctx->Query()->Content());
		}
	}
	catch(Exception& fe)
	{
		return Handler::Error(fe, true);
	}
	catch(std::exception& e)
	{
		return Handler::Error(FUGU_EXCEPT(e.what() ,"DBViewHandler::GetView"), true);
	}
	
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