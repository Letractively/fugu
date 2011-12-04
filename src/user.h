#ifndef __FUGU_USER__
#define __FUGU_USER__

#include "prerequisites.h"
#include "iterators.h"
#include <dbclient.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <boost/thread/shared_mutex.hpp>

//fugu::UserManager maneger;	
//maneger.CreateUser("{ Login: 'test', Password: 'test',  Role: 0, FirstName: 'test', LastName: 'test', About: 'Designer' }");
//maneger.CreateUser("test", "test", fugu::UserRole::SUPERVISOR, "test");
//fugu::UsersIterator iter = maneger.GetUsers();
//while(iter.HasMore()) {
//	fugu::UserPtr user = iter.PeekNextValue();
//	Processing...
//	iter.MoveNext();
//}

namespace fugu {

enum UserRole
{
	SUPERVISOR		= 0x0,
	ADMIN			= 0x1,
	SENIOR_USER		= 0x2,
	USER			= 0x3,
	JUNIOR_USER		= 0x4
};

// Class to store user info
class User : private boost::noncopyable
{
friend class UserManager;

private:
	User(const std::string& login, const std::string& passwordHash, UserRole role, 
		const std::string& email, const std::string& firstName, const std::string& lastName,
		const std::string& about);
	User(const mongo::BSONObj& obj);
	bool MatchPassword(const std::string& password) const;
	void SetPassword(const std::string& password);

public:
	virtual ~User();

	const std::string& Login() const { return _login; }
	const std::string& Email() const { return _email; }
	UserRole Role() const { return _role; }
	const std::string& FirstName() const { return _firstName; }
	const std::string& LastName() const { return _lastName; }
	const std::string& About() const { return _about; }

private:
	std::string _login;
	std::string _passwordHash;
	UserRole _role;
	std::string _email;
	std::string _firstName;
	std::string _lastName;
	std::string _about;
};

typedef std::map<std::string, UserPtr> Users;
typedef MapIterator<Users> UsersIterator;

class UserManager
{
public:
	UserManager();

	// Creates new user by json string, and add it to the database
	UserPtr CreateUser(const std::string& json);

	UserPtr CreateUser(const std::string& login, const std::string& passwordHash, UserRole role, 
						const std::string& email, const std::string& firstName = "", const std::string& lastName = "",  
						const std::string& about = "");

	void DeleteUser(const std::string& login);

	UserPtr GetUser(const std::string& login);

	UsersIterator GetUsers();

private:
	// reconect to database
	void ReConnect();
	// count == 0 - loads all users
	long LoadUsers(long count=0);
	UserPtr CreateUser(const mongo::BSONObj& obj);

private:
	boost::shared_mutex _access;
	Users _users;
	mongo::DBClientConnection _db;
};
/*
boost::shared_mutex _access;
void reader()
{
  // get shared access
  boost::shared_lock lock(_access);

  // now we have shared access
}

void writer()
{
  // get upgradable access
  boost::upgrade_lock lock(_access);

  // get exclusive access
  boost::upgrade_to_unique_lock uniqueLock(lock);
  // now we have exclusive access
}
*/
}

#endif