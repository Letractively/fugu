#include "prerequisites.h"
#include "webapplication.h"
//#include "user.h"
#include "exception.h"
#include "redis4cpp/commands.h"

//#include "uv.h"
//#include "lockfreequeque.h"
//#include "nedmalloc/malloc.c.h"

struct test{};
int main(int argc, char* argv[]) 
{
	try
	{
        //typedef boost::shared_ptr<int> IntPtr;
        //boost::lockfree::fifo<int*> fifo;
        //IntPtr p;
        //fifo.dequeue(p);
        
        //fugu::LockFreeQueue<test> q;
        
		//UserManager* i = nedalloc::New<UserManager>();
		// Check command line arguments.
		//if (argc < 2)
		//{
            //std::cerr << "Usage: fuguservice.exe <confing file path>\n";
			//return 1;
		//}
		// Initialise server.
		fugu::WebApplication app("./fugu.conf");//argv[1]);

		//uv_listen(NULL, 0, NULL);

		// Run the server until stopped.
		app.Run();
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what() << "\n";
	}

	return 0;
}