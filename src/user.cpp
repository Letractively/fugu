#include "user.h"
#include <openssl/sha.h>
#include <iostream>
#include <boost/thread/locks.hpp>
//TOFO: add sha1 password encryption #include <boost/uuid/sha1.hpp>

namespace fugu {

	User::User(const std::string& login, const std::string& passwordHash, UserRole role, const std::string& email,
				const std::string& firstName, const std::string& lastName,  const std::string& about)
		:_login(login)
		,_passwordHash(passwordHash)
		,_email(email)
		,_role(role)
		,_firstName(firstName)
		,_lastName(lastName)
		,_about(about) 
	{}

	User::User(const mongo::BSONObj& obj)
		:_login(obj.getStringField("Login"))
		,_passwordHash(obj.getStringField("Password"))
		,_email(obj.getStringField("Email"))
		,_role((UserRole)obj.getIntField("Role"))
		,_firstName(obj.getStringField("FirstName"))
		,_lastName(obj.getStringField("LastName"))
		,_about(obj.getStringField("About"))
	{}

	User::~User() {}

	bool User::MatchPassword(const std::string& password) const 
	{ 
		return _passwordHash.compare(password) == 0; 
	}

	void User::SetPassword(const std::string& password) {}

	UserManager::UserManager()
	{
		ReConnect();
	}

	UserPtr UserManager::CreateUser(const std::string& json)
	{
		mongo::BSONObj obj = mongo::fromjson(json);

		return CreateUser(obj);
	}

	UserPtr UserManager::CreateUser(const std::string& login, const std::string& passwordHash, UserRole role, 
									const std::string& email, const std::string& firstName, const std::string& lastName,  
									const std::string& about)
	{
		return CreateUser( BSON(mongo::GENOID
							<< "Login" << login 
							<< "Password" << passwordHash
							<< "Email" <<email 
							<< "Role" <<(int)role,
							<< "FirstName" << firstName
							<< "LastName" << lastName
							<< "About" << about));
	}

	UserPtr UserManager::CreateUser(const mongo::BSONObj& obj)
	{
		// get shared access
		//boost::shared_lock<boost::shared_mutex> lock(_access);
		UserPtr user = GetUser(obj.getStringField("Login"));

		if(!user.get()) {

			user.reset(new User(obj));
			{
				// get upgradable access
				boost::upgrade_lock<boost::shared_mutex> lock(_access);
				// get exclusive access
				boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
				_users.insert(std::make_pair<std::string, UserPtr>(user->Login(), user));
			}

			_db.insert("test.fugu.users", obj);

		}
		return user;
	}

	void UserManager::DeleteUser(const std::string& login)
	{
		_db.remove("test.fugu.users", QUERY("Login"<<login));
		_users.erase(login);
	}

	UserPtr UserManager::GetUser(const std::string& login)
	{
		bool dbreloaded = false;
		if(_users.empty())
		{
			LoadUsers();
			dbreloaded = true;
		}

		Users::iterator iter = _users.find(login);
		if(iter !=  _users.end()) {
			return iter->second;
		}
		else {

			if(!dbreloaded) {
				std::auto_ptr<mongo::DBClientCursor> cursor =  _db.query("test.fugu.users", QUERY("Login"<<login));
				if(cursor->more())
					return UserPtr(new User(cursor->next()));
			}
		}

		return UserPtr();
	}

	UsersIterator UserManager::GetUsers()
	{
		if(_users.empty())
			LoadUsers();

		return UsersIterator(_users.begin(), _users.end());
	}

	long UserManager::LoadUsers(long count)
	{
		std::auto_ptr<mongo::DBClientCursor> cursor =  _db.query("test.fugu.users", mongo::Query());
		while(cursor->more()) {
			UserPtr user(new User(cursor->next()));
			_users.insert(std::make_pair<std::string, UserPtr>(user->Login(), user));
		}
		
		return _users.size();
	}

	void UserManager::ReConnect()
	{
		_db.connect("localhost");
	}
}