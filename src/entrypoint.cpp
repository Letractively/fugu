#include "prerequisites.h"
#include "webapplication.h"
#include "user.h"
#include "exception.h"
//#include "nedmalloc/malloc.c.h"

int main(int argc, char* argv[]) 
{
	try
	{
		//UserManager* i = nedalloc::New<UserManager>();
		// Check command line arguments.
		if (argc < 2)
		{
			std::cerr << "Usage: fuguservice.exe <confing file path>\n";
			return 1;
		}
		// Initialise server.
		fugu::WebApplication app(argv[1]);

		// Run the server until stopped.
		app.Run();
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what() << "\n";
	}

	return 0;
}