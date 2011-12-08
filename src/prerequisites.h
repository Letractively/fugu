#ifndef __FUGU_PREREQUISITES__
#define __FUGU_PREREQUISITES__

#define _WIN32_WINNT 0x0500
#define BOOST_ALL_DYN_LINK
#define BOOST_WINDOWS
#define _UNICODE


#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace fugu {

class User;
class Request;
class Response;
class HttpRequest;
class HttpResponse;
class WebServer;
class WebServer;
class QueryContext;
class Session;
class SessionManager;
class Connection;
class Controller;
class ControllerManager;
class ViewData;
typedef Response* ResponsePtr;
typedef boost::shared_ptr<Request> RequestPtr;
typedef boost::shared_ptr<ViewData> ViewDataPtr;
typedef boost::shared_ptr<HttpRequest> HttpRequestPtr;
typedef boost::shared_ptr<QueryContext> QueryContextPtr;
typedef boost::shared_ptr<Session> SessionPtr;
typedef boost::shared_ptr<Connection> ConnectionPtr;
typedef boost::shared_ptr<Controller> ControllerPtr;
typedef boost::shared_ptr<User> UserPtr;
typedef const char* RequestBuffer;
typedef std::string ResponseBuffer;
}

namespace mongo {
class DBClientConnection;
class BSONObj;
class Query;
}

#endif