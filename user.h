#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "person.h"
#include "strings.h"
#include "date.h"
#include "util.h"

class user : public person
{
private:
	enum enObjMode { empty, update, add };
	enObjMode _mode;
	string _username, _password = "";
	int _permissions;
	bool _deleteMark = false;

	struct stLoginRegister;

	string _getLoginRecord(string separator = "#//#")
	{
		return date::getTimeNow() + separator +
		username + separator +
		password + separator +
		to_string(permissions);
	}

	static stLoginRegister _getLoginRegister(string line, string separetor = "#//#")
	{
		vector<string> reg = strings::split(line, separetor);
		
		stLoginRegister loginRegister(reg[0], reg[1], reg[2], reg[3]);

		return loginRegister;
	}

	static vector<stLoginRegister> _loadRegistersFromFile()
	{
		vector<stLoginRegister> registers;
		string line = "";

		std::fstream file;
		file.open("loginRegister.txt", ios::in);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				registers.push_back(_getLoginRegister(line));
			}
		}

		return registers;
	}

	static user _convertLineToUser(string line, string separetor = "#//#")
	{
		vector<string> userInfo = strings::split(line, separetor);

		return user(enObjMode::update, userInfo[0], userInfo[1], userInfo[2], userInfo[3], userInfo[4], userInfo[5], stoi(userInfo[6]));
	}

	static string _convertUserToLine(user user, string separator = "#//#")
	{
		return user.firstName + separator + user.lastName + separator + user.email + separator +
			user.phoneNumber + separator + user._username + separator + user._password + separator + to_string(user._permissions);
	}

	static vector<user> _loadUsersFromFile()
	{
		vector<user> users;
		string line = "";

		std::fstream file;
		file.open("users.txt", ios::in);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				users.push_back(_convertLineToUser(line));
			}
		}

		return users;
	}

	static void _appendToFile(const string& line, string file_name = "users.txt")
	{
		fstream file;
		file.open(file_name, ios::app);

		if (file.is_open())
			file << line << endl;
	}

	static void _saveClientsInFile(vector<user>& users)
	{
		fstream file;
		file.open("users.txt", ios::out);

		if (file.is_open())
		{
			for (user& user : users)
			{
				if (!user._deleteMark)
				{
					file << _convertUserToLine(user) << std::endl;
				}
			}
		}
	}

	void _update()
	{
		vector<user> _vUsers = _loadUsersFromFile();

		for (user& u : _vUsers)
		{
			if (u._username == _username)
			{
				u = *this;
				break;
			}
		}

		_saveClientsInFile(_vUsers);
	}

	void _add()
	{
		_appendToFile(_convertUserToLine(*this));
	}

	static user _getEmptyUser()
	{
		return user(enObjMode::empty, "", "", "", "", "", "", 0);
	}

public:
	user(enObjMode mode, string fname, string lname, string email, string phone, string username, string password, int permissions)
		: person(fname, lname, email, phone),
		_mode(mode), _username(username), _password(password), _permissions(permissions)
	{
	}


	struct stPermisions {
		static constexpr int LIST = 1 << 1;
		static constexpr int ADD = 1 << 2;
		static constexpr int DELETE = 1 << 3;
		static constexpr int UPDATE = 1 << 4;
		static constexpr int FIND = 1 << 5;
		static constexpr int TRANS = 1 << 6;
		static constexpr int MANAGE_USERS = 1 << 7;
		static constexpr int LOGIN_REGISTER = 1 << 8;
	};

	struct stLoginRegister {
		string dateTime;
		string username;
		string password;
		string perm;
	};

	// ---- Getters & Setters
	string getUsername()
	{
		return _username;
	}
	string getPassword()
	{
		return _password;
	}
	int getPermissions()
	{
		return _permissions;
	}

	void setPassword(string password)
	{
		_password = password;
	}
	void setPermission(int perm)
	{
		_permissions = perm;
	}

	__declspec(property(get = getUsername)) string username;
	__declspec(property(get = getPassword, put = setPassword)) string password;
	__declspec(property(get = getPermissions, put = setPermission)) int permissions;

	bool isEmpty()
	{
		return _mode == enObjMode::empty;
	}

	static user find(string username)
	{
		fstream file;
		file.open("users.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				user currentUser = _convertLineToUser(line);

				if (currentUser._username == username)
				{
					file.close();
					return currentUser;
				}
			}
			file.close();
		}

		return _getEmptyUser();
	}

	static user find(string username, string password)
	{
		fstream file;
		file.open("users.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				user currentUser = _convertLineToUser(line);

				if (currentUser._username == username && currentUser._password == password)
				{
					file.close();
					return currentUser;
				}
			}
			file.close();
		}

		return _getEmptyUser();
	}

	enum enSaveStates { failedEmptyObject, success, failedUsernameExists };

	enSaveStates save()
	{
		switch (_mode)
		{
		case enObjMode::empty:
			return enSaveStates::failedEmptyObject;
		case enObjMode::update:
			_update();
			return enSaveStates::success;
		case enObjMode::add:
			if (isUserExist(_username))
				return enSaveStates::failedUsernameExists;
			else
			{
				_add();
				_mode = enObjMode::update;
				return enSaveStates::success;
			}

		}
	}

	static bool isUserExist(const string& username)
	{
		user test_user = user::find(username);
		return (!test_user.isEmpty());
	}

	static user getAddNewUserObject(string username)
	{
		return user(enObjMode::add, "", "", "", "", username, "", 0);
	}

	bool deleteUser()
	{
		vector<user> _vUsers = _loadUsersFromFile();

		for (user& u : _vUsers)
		{
			if (u._username == _username)
			{
				u._deleteMark = true;
			}
		}

		_saveClientsInFile(_vUsers);

		*this = _getEmptyUser();

		return true;
	}

	static vector<user> getUsersList()
	{
		return _loadUsersFromFile();
	}

	static vector<stLoginRegister> getRegistersList()
	{
		return _loadRegistersFromFile();
	}

	bool checkPermissions(int perm)
	{
		return (perm & this->permissions);
	}

	void registerLogin()
	{
		string line = _getLoginRecord();
		_appendToFile(line, "loginRegister.txt");
	}
};

