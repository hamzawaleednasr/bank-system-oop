#pragma once

#include "screen.h"
#include "depositeScreen.h"
#include "withdrawScreen.h"
#include "totalBalancesScreen.h"
#include "transferScreen.h"
#include "transferLogScreen.h"
#include "inputValidate.h"
#include <iostream>


class transactionsScreen : protected screen
{
private:
	enum enTransactionsOptions {
		deposite = 1, withdraw, total_balances, transfer, transfer_log, main_menu
	};

	static short _readTransactionsOption()
	{
		short choice = inputValidate::readIntInRange(1, 6, "\nChoose what do you want to do? [1-6]: ");
		return choice;
	}

	static void _goBackToTransactionsMenu()
	{
		cout << "\nPress any key to return transactions menu . . .";
		system("pause>0");
		showTransactionsMenu();
	}

	static void _showDepositeScreen()
	{
		depositeScreen::showDepositeScreen();
	}

	static void _showWithdrawScreen()
	{
		withdrawScreen::showWithdrawScreen();
	}

	static void _showTotalBalancesScreen()
	{
		totalBalancesScreen::showTotalBalancesScreen();
	}

	static void _showTransferScreen()
	{
		transferScreen::showTransferScreen();
	}

	static void _showTransfersLogScreen()
	{
		transferLogScreen::showTransfers();
	}

	static void _performTransactionsOption(enTransactionsOptions option)
	{
		switch (option)
		{
		case enTransactionsOptions::deposite:
			system("cls");
			_showDepositeScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsOptions::withdraw:
			system("cls");
			_showWithdrawScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsOptions::total_balances:
			system("cls");
			_showTotalBalancesScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsOptions::transfer:
			system("cls");
			_showTransferScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsOptions::transfer_log:
			system("cls");
			_showTransfersLogScreen();
			_goBackToTransactionsMenu();
			break;
		case enTransactionsOptions::main_menu:
			break;
		}
	}

public:
	static void showTransactionsMenu()
	{

		if (!checkRights(user::stPermisions::TRANS))
			return;

		system("cls");
		_printHeader("Transactions Screen");
		std::cout << "========================================================\n";
		std::cout << "                  Transactions Screen                   \n";
		std::cout << "========================================================\n";
		std::cout << "  [1] Deposite.\n";
		std::cout << "  [2] Withdraw.\n";
		std::cout << "  [3] Total Balances.\n";
		std::cout << "  [4] Transfer.\n";
		std::cout << "  [5] Transfer Log.\n";
		std::cout << "  [6] Main Menu.\n";
		std::cout << "========================================================";
		_performTransactionsOption((enTransactionsOptions)_readTransactionsOption());
	}
};

