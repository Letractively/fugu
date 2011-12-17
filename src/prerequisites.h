#ifndef __FUGU_PREREQUISITES__
#define __FUGU_PREREQUISITES__

#define _WIN32_WINNT 0x0500
#define BOOST_ALL_DYN_LINK
#define BOOST_WINDOWS
#define _UNICODE

#define FUGU_MULTI_THREADING

#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace mongo {

class DBClientConnection;
class BSONObj;
class Query;

}

namespace fugu {

typedef mongo::BSONObj JsonObj;
typedef boost::shared_ptr<std::string> StringPtr;

class User;
typedef boost::shared_ptr<User> UserPtr;

class Request;
typedef boost::shared_ptr<Request> RequestPtr;

class Reply;
typedef Reply* ReplyPtr;

class Session;
class SessionManager;
typedef boost::shared_ptr<Session> SessionPtr;

class Context;
typedef boost::shared_ptr<Context> ContextPtr;

class Connection;
typedef boost::shared_ptr<Connection> ConnectionPtr;

class Route;
typedef boost::shared_ptr<Route> RoutePtr;

class ViewData;
typedef boost::shared_ptr<ViewData> ViewDataPtr;

class Query;
typedef boost::shared_ptr<Query> QueryPtr;

class Handler;
typedef boost::shared_ptr<Handler> HandlerPtr;

class WebServer;
class Config;
class Config;
class HandlerRouter;
}

#endif