#pragma once

#include <iostream>
#include "screen.h"
#include "inputValidate.h"
#include "currencyListScreen.h"
#include "findCurrencyScreen.h"
#include "updateCurrencyRateScreen.h"
#include "currencyCalculatorScreen.h"

class currencyScreen : protected screen
{
private:
	enum enCurrencyMenuOptions {
		list = 1, find, update_rate, calc, main_menu 
	};

	static short _readCurrencyMenuOption()
	{
		short choice = inputValidate::readIntInRange(1, 5, "\nChoose what do you want to do? [1-5]: ");
		return choice;
	}

	static void _goBackToCurrencyMenu()
	{
		cout << "\nPress any key to return currency menu . . .";
		system("pause>0");
		showCurrencyMenu();
	}

	static void _showListCurrenciesScreen()
	{
		currencyListScreen::showCurrencies();
	}

	static void _showFindCurrenciesScreen()
	{
		findCurrencyScreen::findCurrency();
	}

	static void _showUpdateRateScreen()
	{
		updateCurrencyRateScreen::updateRate();
	}

	static void _showCurrencyCalcScreen()
	{
		currencyCalculatorScreen::currencyCalculator();
	}

	static void _performCurrencyMenuOption(enCurrencyMenuOptions option)
	{
		switch (option)
		{
		case enCurrencyMenuOptions::list:
			system("cls");
			_showListCurrenciesScreen();
			_goBackToCurrencyMenu();
			break;
		case enCurrencyMenuOptions::find:
			system("cls");
			_showFindCurrenciesScreen();
			_goBackToCurrencyMenu();
			break;
		case enCurrencyMenuOptions::update_rate:
			system("cls");
			_showUpdateRateScreen();
			_goBackToCurrencyMenu();
			break;
		case enCurrencyMenuOptions::calc:
			system("cls");
			_showCurrencyCalcScreen();
			_goBackToCurrencyMenu();
			break;
		case enCurrencyMenuOptions::main_menu: {}
		}
	}

public:
	static void showCurrencyMenu()
	{
		system("cls");
		_printHeader("Currency Screen");
		cout << "==================================================\n";
		cout << "                   Currency Menu                  \n";
		cout << "==================================================\n";
		cout << "  [1] Show Currencies List.\n";
		cout << "  [2] Find Currency.\n";
		cout << "  [3] Update Rate.\n";
		cout << "  [4] Currency Calculator.\n";
		cout << "  [5] Main Menu.\n";
		cout << "==================================================";
		_performCurrencyMenuOption((enCurrencyMenuOptions)_readCurrencyMenuOption());
	}
};

