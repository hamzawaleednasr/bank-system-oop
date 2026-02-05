#pragma once

#include "screen.h"
#include "listUsersScren.h"
#include "addUserScreen.h"
#include "deleteUserScreen.h"
#include "updateUserScreen.h"
#include "findUserScreen.h"
#include "inputValidate.h"
#include <iostream>


class manageUsersScreen : protected screen
{
private:
	enum enManageUsersOptions {
		list = 1, add, del, update, find, main_menu
	};

	static short _readManageUsersOption()
	{
		short choice = inputValidate::readIntInRange(1, 6, "\nChoose what do you want to do? [1-6]: ");
		return choice;
	}

	static void _goBackToManageUsersMenu()
	{
		cout << "\nPress any key to return manage users menu . . .";
		system("pause>0");
		showManageUsersMenu();
	}

	static void _showListUsersScreen()
	{
		listUsersScreen::showUsers();
	}

	static void _showAddUserScreen()
	{
		addUserScreen::addNewUser();
	}		

	static void _showDeleteUserScreen()
	{
		deleteUserScreen::deleteUser();
	}

	static void _showUpdateUserScreen()
	{
		updateUserScreen::updateUser();
	}

	static void _showFindUserScreen()
	{
		findUserScreen::findUser();
	}

	static void _performManageUsersOption(enManageUsersOptions option)
	{
		switch (option)
		{
		case enManageUsersOptions::list:
			system("cls");
			_showListUsersScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersOptions::add:
			system("cls");
			_showAddUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersOptions::update:
			system("cls");
			_showUpdateUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersOptions::del:
			system("cls");
			_showDeleteUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersOptions::find:
			system("cls");
			_showFindUserScreen();
			_goBackToManageUsersMenu();
			break;
		case enManageUsersOptions::main_menu:
			break;
		}
	}

public:
	static void showManageUsersMenu()
	{

		if (!checkRights(user::stPermisions::MANAGE_USERS))
			return;

		system("cls");
		_printHeader("Manage Users Screen");
		std::cout << "========================================================\n";
		std::cout << "                      Manage Users                      \n";
		std::cout << "========================================================\n";
		std::cout << "  [1] List Users.\n";
		std::cout << "  [2] Add New User.\n";
		std::cout << "  [3] Delete User.\n";
		std::cout << "  [4] Update User .\n";
		std::cout << "  [5] Find User.\n";
		std::cout << "  [6] Main Menu.\n";
		std::cout << "========================================================";
		_performManageUsersOption((enManageUsersOptions)_readManageUsersOption());
	}
};

