#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "currency.h"
#include "inputValidate.h"

class findCurrencyScreen : protected screen
{
private:
	static void printCurrency(currency c)
	{
		cout << "\nClient card:";
		cout << "\n------------------------------------";
		cout << "\nCountry       : " << c.getCountry();
		cout << "\nCode          : " << c.getCode();
		cout << "\nCurrency Name : " << c.getCurrencyName();
		cout << "\nRate (1$)     : " << c.getRate();
		cout << "\n------------------------------------\n";
	}

public:
	static void findCurrency()
	{

		_printHeader("Find Currency Screen");

		cout << "Enter the code or country: ";
		string keyword = inputValidate::readString();

		while (!currency::isCurrencyExist(keyword))
		{
			cout << "\nCode & Country are not found, choose another one: ";
			keyword = inputValidate::readString();
		}

		currency foundedCurrency = currency::find(keyword);

		if (!foundedCurrency.isEmpty())
			cout << "\nCurrency was found :-)\n";
		else
			cout << "\nCurrency was NOT found :-(\n";

		printCurrency(foundedCurrency);
	}
};

