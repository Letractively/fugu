#ifndef __FUGU_SESSION__
#define __FUGU_SESSION__

#include "prerequisites.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/shared_mutex.hpp>

namespace fugu {

typedef std::map<std::string, ControllerPtr> Controllers;
typedef std::map<std::string, SessionPtr> Sessions;

// User session
class Session : private boost::noncopyable
{
public:
	Session();
	~Session();
	const std::string& Id() const;
	UserPtr User()const;
	bool HasExpired();

private:
	// Session identifier
	std::string _id;
	// Owner of the session
	UserPtr _user;
	// Session start time
	boost::posix_time::ptime _signUpAt;
	// The last user activity
	boost::posix_time::ptime _lastActivityAt;
	// Session controllers, the controllers can cache the states and data
	Controllers _controllers;
};

// Manager of the user sessions
class SessionManager
{
public:
	SessionManager();
	~SessionManager();
	// Session id is cookie value with name "SESSION_HASH"
	SessionPtr GetSession(const std::string& sessionId, ConnectionPtr connection);
	// Collect expired sessions
	long CleanupSessions();

private:
	void DestroySession(const std::string& sessionId);

private:
	boost::shared_mutex _access;
	Sessions _sessions;
};

}

#endif