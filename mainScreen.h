#pragma once

#include <iostream>
#include "screen.h"
#include "inputValidate.h"
#include "clientListScreen.h"
#include "addClientScreen.h"
#include "deleteClientScreen.h"
#include "updateClientScreen.h"
#include "findClientScreen.h"
#include "transactionsScreen.h"
#include "manageUsersScreen.h"
#include "loginRegisterScreen.h"
#include "currencyScreen.h"
#include "login.h"

class mainScreen : protected screen
{
private:
	enum enMainMenuOptions {
		list = 1, add, del, update, find, trans, manage_users, registers, currency_exchange, logout
	};

	static short _readMainMenuOption()
	{
		short choice = inputValidate::readIntInRange(1, 10, "\nChoose what do you want to do? [1-10]: ");
		return choice;
	}

	static void _goBackToMainMenu()
	{
		cout << "\nPress any key to return main menu . . .";
		system("pause>0");
		showMainMenu();
	}

	static void _showListClientsScreen()
	{
		clientListScreen::showClients();
	}

	static void _showAddClientScreen()
	{
		addClientScreen::addNewClient();
	}

	static void _showDeleteClientScreen()
	{
		deleteClientScreen::deleteClient();
	}

	static void _showUpdateClientScreen()
	{
		updateClientScreen::updateClient();
	}

	static void _showFindClientScreen()
	{
		findClientScreen::findClient();
	}

	static void _showTransactionsMenuScreen()
	{
		transactionsScreen::showTransactionsMenu();
	}

	static void _showManageUsersScreen()
	{
		manageUsersScreen::showManageUsersMenu();
	}

	static void _showLoginRegisterScreen()
	{
		loginRegisterScreen::showRegisters();
	}

	static void _showCurrencyMenuScreen()
	{
		currencyScreen::showCurrencyMenu();
	}

	static void _showLogoutScreen()
	{
		currentUser = user::find("", "");
	}

	static void _performMainMenuOption(enMainMenuOptions option)
	{
		switch (option)
		{
		case enMainMenuOptions::list:
			system("cls");
			_showListClientsScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOptions::add:
			system("cls");
			_showAddClientScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOptions::del:
			system("cls");
			_showDeleteClientScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOptions::update:
			system("cls");
			_showUpdateClientScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOptions::find:
			system("cls");
			_showFindClientScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOptions::trans:
			system("cls");
			_showTransactionsMenuScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOptions::manage_users:
			system("cls");
			_showManageUsersScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOptions::registers:
			system("cls");
			_showLoginRegisterScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOptions::currency_exchange:
			system("cls");
			_showCurrencyMenuScreen();
			_goBackToMainMenu();
			break;
		case enMainMenuOptions::logout:
			system("cls");
			_showLogoutScreen();
			break;
		}
	}

public:
	static void showMainMenu()
	{
		system("cls");
		_printHeader("Main Screen");
		cout << "==================================================\n";
		cout << "                    Main Menu                     \n";
		cout << "==================================================\n";
		cout << "  [1] Show Client List.\n";
		cout << "  [2] Add New Client.\n";
		cout << "  [3] Delete Client.\n";
		cout << "  [4] Update Client Info.\n";
		cout << "  [5] Find Client.\n";
		cout << "  [6] Transactions.\n";
		cout << "  [7] Manage Users.\n";
		cout << "  [8] Login Register.\n";
		cout << "  [9] Currency Exchange.\n";
		cout << "  [10] Logout.\n";
		cout << "==================================================";
		_performMainMenuOption((enMainMenuOptions)_readMainMenuOption());
	}
};

