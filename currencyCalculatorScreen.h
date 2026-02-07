#pragma once

#include <iostream>
#include <string>
#include "inputValidate.h"
#include "screen.h"
#include "currency.h"

using namespace std;

class currencyCalculatorScreen : protected screen
{
private:
	static currency _getValidCurrency()
	{
		string keyword = inputValidate::readString();
		currency c = currency::find(keyword);

		while (c.isEmpty())
		{
			cout << "\nThis currency is not found, try another: ";
			keyword = inputValidate::readString();
			c = currency::find(keyword);
		}

		return c;
	}

public:
	static void currencyCalculator()
	{
		char con = 'n';

		do {
			system("cls");

			_printHeader("Currency Calculator Screen");

			cout << "\nEnter currency1: ";
			currency from = _getValidCurrency();

			cout << "\nEnter currency2: ";
			currency to = _getValidCurrency();

			cout << "\nEnter amount: ";
			double amount = inputValidate::readDouble("");

			double result;

			if (from.getCode() == "USD")
				result = to.getRate() * amount;
			else if (to.getCode() == "USD")
				result = amount / from.getRate();
			else
			{
				double fromInDollars = amount / from.getRate();
				result = fromInDollars * to.getRate();
			}

			cout << "\n\n" << amount << " " << from.getCode() << " = " << result << " " << to.getCode() << endl;

			cout << "\nDo you want to make another exchange? [y/n]: ";
			cin >> con;
		} while (con == 'y' || con == 'Y');
	}
};

