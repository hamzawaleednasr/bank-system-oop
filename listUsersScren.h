#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "screen.h"
#include "user.h"
#include "util.h"

using namespace std;

class listUsersScreen : protected screen
{
private:
	static void printUser(user& u)
	{
		cout << "| " << setw(15) << left << u.username;
		cout << "| " << setw(20) << left << u.fullName();
		cout << "| " << setw(20) << left << u.phoneNumber;
		cout << "| " << setw(25) << left << util::decryption(u.password, 1026);
		cout << "| " << setw(5) << left << u.permissions << endl;
	}

public:
	static void showUsers()
	{
		vector<user> users = user::getUsersList();

		_printHeader("Users List Screen", "  (" + to_string(users.size()) + ") User(s).");

		cout << "------------------------------------------------------------------------------------------------------\n";
		cout << "| " << left << setw(15) << "Username" << "| " << left << setw(20) << "Full Name" << "| " << left << setw(20) << "Phone Number" << "| " << left << setw(25) << "Password" << "| " << left << std::setw(5) << "Permissions" << endl;
		cout << "------------------------------------------------------------------------------------------------------\n";

		if (users.size() == 0)
			cout << "\nThere are no users.\n";
		else
			for (user& u : users)
				printUser(u);

		cout << "------------------------------------------------------------------------------------------------------\n";
	}
};

