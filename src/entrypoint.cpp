#include "prerequisites.h"
#include "webapplication.h"
#include "user.h"
#include "exception.h"
//#include "nedmalloc/nedmalloc.h"

int main(int argc, char* argv[]) 
{
	try
	{
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

 //   std::string message;
 //   int port;

 //   po::options_description desc("Test options");
 //   desc.add_options()
 //       ("port", po::value<int>(&port)->default_value(8888), "The port number to open up")
 //       ("message", po::value<std::string>(&message)->default_value("<html><h1>Hello world!</h1></html>"), "Message to display");

 //   po::variables_map vm;
 //   po::store(po::parse_command_line(argc, argv, desc), vm);
 //   po::notify(vm);

	//std::ostringstream users;
	//fugu::UsersIterator iter = maneger.GetUsers();
	//while(iter.HasMore()) {
	//	fugu::UserPtr user = iter.PeekNextValue();
	//	users << "User name: " << user->Login()
	//			<< "Email: " << user->Email() << "<br/>";

	//	iter.MoveNext();
	//}
	//message = users.str();

 //   std::ostringstream response;
 //   response<<"HTTP/1.0 200 OK\r\n"
 //           <<"Content-Type: text/html; charset=UTF-8\r\n"
 //           <<"Content-Length: "<<message.length()<<"\r\n"
 //           <<"\r\n"<<message<<"\r\n";
 //   message = response.str();

 //   try {
 //       fugu::WebServer service(message, port);
 //       service.Run();
 //   }
 //   catch (const std::exception& e)
 //   {
 //       std::cerr<<e.what()<<std::endl; // spew
 //   }
	return 0;
}