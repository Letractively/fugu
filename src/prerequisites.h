#ifndef __FUGU_PREREQUISITES__
#define __FUGU_PREREQUISITES__

/*
#define _WIN32_WINNT 0x0500
#define BOOST_ALL_DYN_LINK
#define BOOST_WINDOWS
#define _UNICODE
*/

#define FUGU_MULTI_THREADING

#include <map>
#include <vector>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>


//TODO: fast allocation
//#include <boost/pool/object_pool.hpp>
//#include <boost/pool/pool_alloc.hpp>
//typedef std::basic_string<char, std::char_traits<char>, boost::fast_pool_allocator<char> > String; 
//typedef boost::shared_ptr<fugu::String> StringPtr;
namespace mongo {

class DBClientConnection;
class BSONObj;
class Query;

}

namespace fugu {

class RedisCommandContext;
typedef boost::shared_ptr<RedisCommandContext> RedisCommandContextPtr;

class RedisDBConnection;
typedef boost::shared_ptr<RedisDBConnection> RedisDBConnectionPtr;

//typedef mongo::BSONObj JsonObj;
//typedef boost::shared_ptr<mongo::DBClientConnection> DBConnectionPtr;

typedef boost::shared_ptr<std::string> StringPtr;

class User;
typedef boost::shared_ptr<User> UserPtr;

class Request;
typedef boost::shared_ptr<Request> RequestPtr;

class Reply;
typedef boost::shared_ptr<Reply> ReplyPtr;

class HtmlReply;
typedef boost::shared_ptr<HtmlReply> HtmlReplyPtr;

class JsonReply;
typedef boost::shared_ptr<JsonReply> JsonReplyPtr;

class Session;
class SessionManager;
typedef boost::shared_ptr<Session> SessionPtr;

class Context;
typedef boost::shared_ptr<Context> ContextPtr;

class Connection;
typedef boost::shared_ptr<Connection> ConnectionPtr;

class Route;
typedef boost::shared_ptr<Route> RoutePtr;
typedef std::map<std::string, RoutePtr> Routes;

class ViewData;
typedef boost::shared_ptr<ViewData> ViewDataPtr;

class Query;
typedef boost::shared_ptr<Query> QueryPtr;

class Handler;
typedef Handler* HandlerPtr;
//typedef boost::shared_ptr<Handler> HandlerPtr;

class JsonModel;
typedef boost::shared_ptr<JsonModel> JsonModelPtr;

class JsonModelStorage;
typedef boost::shared_ptr<JsonModelStorage> JsonModelStoragePtr;

class Config;
typedef boost::shared_ptr<Config> ConfigPtr;

class Database;
typedef boost::shared_ptr<Database> DatabasePtr;

class WebServer;
class Config;
class HandlerRouter;
}

#endif