#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "user.h"
#include "inputValidate.h"

class findUserScreen : protected screen
{
private:
	static void printUser(user u)
	{
		cout << "\nUser card:";
		cout << "\n------------------------------------";
		cout << "\nFirst name: " << u.firstName;
		cout << "\nLast name: " << u.lastName;
		cout << "\nEmail: " << u.email;
		cout << "\nPhone Number: " << u.phoneNumber;
		cout << "\nUsername: " << u.username;
		cout << "\nPasswords: " << u.password;
		cout << "\nPermissions: " << u.permissions;
		cout << "\n------------------------------------\n";
	}

public:
	static void findUser()
	{
		_printHeader("Find User Screen");

		cout << "Enter the username: ";
		string username = inputValidate::readString();

		while (!user::isUserExist(username))
		{
			cout << "\nUsername is not found, choose another one: ";
			username = inputValidate::readString();
		}

		user user = user::find(username);
		printUser(user);
	}
};

