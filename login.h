#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "user.h"
#include "mainScreen.h"
#include "inputValidate.h"

using namespace std;

static bool lock = false;
static short trials = 2;

class loginScreen : protected screen
{
private:
	static void _login()
	{
		bool loginFailed = false;
		string username, password;

		do
		{

			if (loginFailed)
			{
				cout << "\nInvalid username/password, try again . . .\n";
				trials--; lock = trials > 0 ? false : true;
				cout << "You have " << trials+1 << " trials to login.\n";
			}

			cout << "\nEnter username: ";
			username = inputValidate::readString();

			cout << "Enter password: ";
			password = inputValidate::readString();

			currentUser = user::find(username, util::encryption(password, 1026));
			loginFailed = currentUser.isEmpty();

		} while (loginFailed && trials > 0);

		if (!lock)
		{
			currentUser.registerLogin();
			mainScreen::showMainMenu();
		}
		else
			cout << "\nSystem Locked after 3 tries.\n";
	}

public:
	static void showLoginScreen()
	{
		system("cls");
		_printHeader("Login Screen");
		_login();
	}
};