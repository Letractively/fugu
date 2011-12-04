#ifndef __FUGU_REQUEST_ROUTER__
#define __FUGU_REQUEST_ROUTER__

#include "prerequisites.h"

namespace fugu {

// The common handler for all incoming requests.
class RequestRouter : private boost::noncopyable
{
	public:
		// Construct with a directory containing files to be served.
		explicit RequestRouter(const std::string& root);

		// Handle a request and produce a reply.
		void Route(const HttpRequest& req, HttpResponse& rep);

	private:
		// Perform URL-decoding on a string. Returns false if the encoding was invalid.
		static bool UrlDecode(const std::string& in, std::string& out);
	private:
		// The directory containing the files to be served.
		std::string _root;
};

}

#endif