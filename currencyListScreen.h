#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "screen.h"
#include "currency.h"

using namespace std;

class currencyListScreen : protected screen
{
private:
	static void printCurrency(currency& c)
	{
		cout << "| " << setw(30) << left << c.getCountry();
		cout << "| " << setw(10) << left << c.getCode();
		cout << "| " << setw(40) << left << c.getCurrencyName();
		cout << "| " << setw(15) << left << c.getRate() << endl;
	}

public:
	static void showCurrencies()
	{
		vector<currency> currencies = currency::getCurrenciesList();

		_printHeader("Currencies List Screen", "  (" + to_string(currencies.size()) + ") Currency(s).");

		cout << "------------------------------------------------------------------------------------------------------\n";
		cout << "| " << left << setw(30) << "Country" << "| " << left << setw(10) << "Code" << "| " << left << setw(40) << "Currency name" << "| " << left << setw(15) << "Rate" << endl;
		cout << "------------------------------------------------------------------------------------------------------\n";

		if (currencies.size() == 0)
			cout << "\nThere are no currencies.\n";
		else
			for (currency& c : currencies)
				printCurrency(c);

		cout << "------------------------------------------------------------------------------------------------------\n";
	}
};

