#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "currency.h"
#include "inputValidate.h"

class updateCurrencyRateScreen : protected screen
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
	static void updateRate()
	{

		_printHeader("Find Currency Screen");

		cout << "Enter the Currency code or country: ";
		string keyword = inputValidate::readString();

		while (!currency::isCurrencyExist(keyword))
		{
			cout << "\nCurrency is not found, choose another one: ";
			keyword = inputValidate::readString();
		}

		currency toUpdateCurrency = currency::find(keyword);
		printCurrency(toUpdateCurrency);

		cout << "\nAre you sure you want to update the rate of this currency [y/n]: ";
		char wantToDelete = 'n';
		cin >> wantToDelete;

		if (wantToDelete == 'Y' || wantToDelete == 'y')
		{
			cout << "\n\nUpdate Rate:\n";
			cout << "------------------";
			float newRate = inputValidate::readDouble("\nEnter new rate: ");
			
			toUpdateCurrency.updateRate(newRate);

			cout << "\nRate updated successfully! :-)\n";
		}
	}
};

