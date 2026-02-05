#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "user.h"
#include "inputValidate.h"

using namespace std;

class deleteUserScreen : protected screen
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
		cout << "\nAccount Number: " << u.username;
		cout << "\nPassword: " << u.password;
		cout << "\nPermissions: " << u.permissions;
		cout << "\n------------------------------------\n";
	}

public:
	static void deleteUser()
	{

		_printHeader("Delete User Screen");

		cout << "Enter the username: ";
		string username = inputValidate::readString();

		while (!user::isUserExist(username))
		{
			cout << "\nUsername is not found, choose another one: ";
			username = inputValidate::readString();
		}

		user deleteUser = user::find(username);
		printUser(deleteUser);

		cout << "\nAre you sure you want to delete this user [y/n]: ";
		char wantToDelete = 'n';
		cin >> wantToDelete;

		if (wantToDelete == 'Y' || wantToDelete == 'y')
		{
			if (deleteUser.deleteUser())
				cout << "\nUser deleted successfully :-)\n";
			else
				cout << "\nError User was not deleted!\n";
		}
	}
};

