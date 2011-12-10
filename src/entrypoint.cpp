#include "prerequisites.h"
#include "webapplication.h"
#include "user.h"
#include "exception.h"
#include "config.h"
//#include "nedmalloc/nedmalloc.h"

int main(int argc, char* argv[]) 
{
	try
	{
		fugu::Config config("fugu.conf");

		//UserManager* i = nedalloc::New<UserManager>();
		// Check command line arguments.
		if (argc != 5)
		{
			std::cerr << "Usage: http_server <address> <port> <threads> <doc_root>\n";
			std::cerr << "  For IPv4, try:\n";
			std::cerr << "    http_server 0.0.0.0 80 1 .\n";
			std::cerr << "  For IPv6, try:\n";
			std::cerr << "    http_server 0::0 80 1 .\n";
			return 1;
		}

		// Initialise server.
		std::size_t numThreads = boost::lexical_cast<std::size_t>(argv[3]);
		fugu::WebApplication app(argv[1], argv[2], argv[4], numThreads);

		// Run the server until stopped.
		app.Run();
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what() << "\n";
	}

	return 0;
}