#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "user.h"
#include "util.h"
#include "inputValidate.h"

class addUserScreen : protected screen
{
private:
	static int readPermissions()
	{
		int perm = 0;
		char isHave;

		std::cout << "\nDo you want to give full access? [y/n]: ";
		std::cin >> isHave;

		if (isHave == 'Y' || isHave == 'y')
			perm = -1;
		else
		{
			std::cout << "\nList clients? [y/n]: ";
			std::cin >> isHave;
			if (isHave == 'Y' || isHave == 'y')
				perm += user::stPermisions::LIST;

			std::cout << "\nAdd clients? [y/n]: ";
			std::cin >> isHave;
			if (isHave == 'Y' || isHave == 'y')
				perm += user::stPermisions::ADD;

			std::cout << "\nDelete clients? [y/n]: ";
			std::cin >> isHave;
			if (isHave == 'Y' || isHave == 'y')
				perm += user::stPermisions::DELETE;

			std::cout << "\nUpdate clients? [y/n]: ";
			std::cin >> isHave;
			if (isHave == 'Y' || isHave == 'y')
				perm += user::stPermisions::UPDATE;

			std::cout << "\nFind clients? [y/n]: ";
			std::cin >> isHave;
			if (isHave == 'Y' || isHave == 'y')
				perm += user::stPermisions::FIND;

			std::cout << "\nTransactions? [y/n]: ";
			std::cin >> isHave;
			if (isHave == 'Y' || isHave == 'y')
				perm += user::stPermisions::TRANS;

			std::cout << "\nManage users? [y/n]: ";
			std::cin >> isHave;
			if (isHave == 'Y' || isHave == 'y')
				perm += user::stPermisions::MANAGE_USERS;

			std::cout << "\nShow Login Registers? [y/n]: ";
			std::cin >> isHave;
			if (isHave == 'Y' || isHave == 'y')
				perm += user::stPermisions::LOGIN_REGISTER;

		}

		return perm;
	}

	static void readUserInfo(user& user)
	{
		cout << "\nEnter first name: ";
		user.firstName = inputValidate::readString();

		cout << "Enter last name: ";
		user.lastName = inputValidate::readString();

		cout << "Enter email: ";
		user.email = inputValidate::readString();

		cout << "Enter phone number: ";
		user.phoneNumber = inputValidate::readString();

		cout << "Enter Password: ";
		user.password = inputValidate::readString();

		user.permissions = readPermissions();
	}

	static void printUser(user u)
	{
		cout << "\nUser card:";
		cout << "\n------------------------------------";
		cout << "\nFirst name: " << u.firstName;
		cout << "\nLast name: " << u.lastName;
		cout << "\nEmail: " << u.email;
		cout << "\nPhone Number: " << u.phoneNumber;
		cout << "\nAccount Number: " << u.username;
		cout << "\nPasswords: " << u.password;
		cout << "\nPermissions: " << u.permissions;
		cout << "\n------------------------------------\n";
	}

public:
	static void addNewUser()
	{

		_printHeader("Add New User Screen");

		cout << "Enter the username: ";
		string username = inputValidate::readString();

		while (user::isUserExist(username))
		{
			cout << "\nUsername is already in use, choose another one: ";
			username = inputValidate::readString();
		}

		user newUser = user::getAddNewUserObject(username);
		cout << "\nCreate New User:";
		cout << "\n----------------------------";
		readUserInfo(newUser);

		newUser.password = util::encryption(newUser.password, 1026);
		user::enSaveStates result = newUser.save();

		switch (result)
		{
		case user::enSaveStates::success:
			cout << "\nUser Added Successfully :-)\n";
			printUser(newUser);
			break;
		case user::enSaveStates::failedEmptyObject:
			cout << "\nError user was not saved because it's Empty";
			break;
		case user::enSaveStates::failedUsernameExists:
			cout << "\nError user was not saved because username is used!\n";
			break;
		}
	}
};

