#include "session.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/thread/locks.hpp>

namespace fugu {

Session::Session(UserPtr user)
	:_user(user)
	,_id(boost::lexical_cast<std::string>(boost::uuids::random_generator()()) )
	,_signUpAt(boost::posix_time::second_clock::universal_time())
	,_lastActivityAt(boost::posix_time::second_clock::universal_time())
{
}

Session::~Session()
{
}

const std::string& Session::Id() const
{
	return _id;
}

UserPtr Session::User()const
{
	return _user;
}

bool Session::HasExpired()
{
	return false;
}

SessionManager::SessionManager()
{
}

SessionManager::~SessionManager()
{
}

SessionPtr SessionManager::CreateSession(UserPtr user)
{
	SessionPtr session(new Session(user));
	{
		// Get upgradable access
		boost::upgrade_lock<boost::shared_mutex> lock(_access);
		// Get exclusive access
		boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
		_sessions.insert(std::make_pair<std::string, SessionPtr>(session->Id(), session));
	}

	return session;
}

SessionPtr SessionManager::GetSession(const std::string& sessionId)
{
	SessionPtr session;
	{
		// get shared access
		boost::shared_lock<boost::shared_mutex> lock(_access);
		Sessions::iterator iter = _sessions.find(sessionId);
		if(iter != _sessions.end())
			return iter->second;
	}

	return SessionPtr();
}


long SessionManager::CleanupSessions()
{
	return 0;
}

void SessionManager::DestroySession(const std::string& sessionId)
{
}

}