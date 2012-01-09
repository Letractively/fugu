#include "templatepagehandler.h"
#include "config.h"
#include "context.h"
#include "database.h"
#include "jsonreply.h"
#include "query.h"
#include "jsonmodel.h"
#include "viewdata.h"
#include "exception.h"

namespace fugu {

//StringPtr str = ReplaceAll(ReplaceAll(ReplaceAll(pattern, 
//                       "{{first_name}}", "Homer"), 
//                       "{{last_name}}", "Simpson"), 
//                       "{{location}}", "Springfield");
StringPtr ReplaceAll(StringPtr str, const std::string &remove, const std::string &insert)
{
	std::string::size_type pos = 0;
	while ((pos = str->find(remove, pos)) != std::string::npos)
	{
	    str->replace(pos, remove.size(), insert);
	    pos++;
	}

    return str;
}

StringPtr ReplaceAll(StringPtr str, const std::string &remove, StringPtr insert)
{
	std::string::size_type pos = 0;
    while ((pos = str->find(remove, pos)) != std::string::npos)
    {
        str->replace(pos, remove.size(), *insert);
        pos++;
    }

    return str;
}

ReplyPtr TempaltePageHandler::Process(ContextPtr ctx)
{
	try
	{
		StringPtr page(new std::string(ctx->Cfg()->PageTemplate()));

		ReplaceAll(ReplaceAll(page, 
			"{{VIEWS}}", ctx->Db()->Views()->AllAsJson()), 
			"{{CURRENT_VIEW}}", ctx->Query()->HasView() ?  "'" + ctx->Query()->ViewName() + "'" : "null"); 


		return Html(page);
	}
	catch(Exception& fe)
	{
		return Handler::Error(fe, true);
	}
	catch(std::exception& e)
	{
		return Handler::Error(FUGU_EXCEPT(e.what() ,"TempaltePageHandler::Process"), true);
	}
}

Handler* TempaltePageHandlerFactory::CreateImpl()
{
	return new TempaltePageHandler();
}

const std::string& TempaltePageHandlerFactory::Name() const
{
	const static std::string TEMPLATE_PAGE_HANDLER = "templatepagehandler";
	return TEMPLATE_PAGE_HANDLER;
}

}