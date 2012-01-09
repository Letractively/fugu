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

	if(url.compare("/getview") == 0)
		return GetView(ctx);

	if(url.compare("/getallviews") == 0)
		return GetAllViews(ctx);

	if(url.compare("/saveview") == 0)
		return UpdateView(ctx);

	if(url.compare("/deleteview") == 0)
		return DeleteView(ctx);

	FUGU_THROW("Unknown url:'" + url + "'", "DBViewHandler::Process");
}


ReplyPtr DBViewHandler::GetAllViews(ContextPtr ctx)
{
	try
	{
		JsonReplyPtr reply(new JsonReply());
		reply->SetJson(ctx->Db()->Views()->AllAsJson());
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

ReplyPtr DBViewHandler::DeleteView(ContextPtr ctx)
{
	try
	{
		std::string viewName = ctx->Query()->Content().getStringField("ViewName");
		ctx->Db()->Views()->Delete(viewName);
		return GetAllViews(ctx);
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