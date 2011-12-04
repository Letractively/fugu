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
friend class SessionManager;
private:
	Session(UserPtr user);

public:
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
	// Create new session
	SessionPtr CreateSession(UserPtr user);
	// Session id is cookie value with name "FUGU_SESSION_HASH"
	SessionPtr GetSession(const std::string& sessionId);
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