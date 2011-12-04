#ifndef __FUGU_QUERY_CONTEXT__
#define __FUGU_QUERY_CONTEXT__

#include "prerequisites.h"
#include "httprequest.h"
#include "HttpResponse.h"

namespace fugu {

class QueryContext
{
	public:
		QueryContext() {}
		virtual ~QueryContext() {}

		SessionPtr Session() { return _session; } 
		const HttpRequest& Request() { return _request; }
		HttpResponse& Response() { return _response; }

	private:
		SessionPtr _session;
		HttpRequest _request;
		HttpResponse _response;
};

}

#endif