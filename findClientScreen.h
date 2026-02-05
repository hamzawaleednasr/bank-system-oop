#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "client.h"
#include "inputValidate.h"

class findClientScreen : protected screen
{
private:
	static void printClient(client c)
	{
		cout << "\nClient card:";
		cout << "\n------------------------------------";
		cout << "\nFirst name: " << c.firstName;
		cout << "\nLast name: " << c.lastName;
		cout << "\nEmail: " << c.email;
		cout << "\nPhone Number: " << c.phoneNumber;
		cout << "\nAccount Number: " << c.accountNumber;
		cout << "\nPIN code: " << c.pin;
		cout << "\nBalance: " << c.balance;
		cout << "\n------------------------------------\n";
	}

public:
	static void findClient()
	{

		if (!checkRights(user::stPermisions::FIND))
			return;

		_printHeader("Find Client Screen");

		cout << "Enter the account number: ";
		string accountNumber = inputValidate::readString();

		while (!client::isClientExist(accountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accountNumber = inputValidate::readString();
		}

		client foundedClient = client::find(accountNumber);

		if (!foundedClient.isEmpty())
			cout << "\nClient was found :-)\n";
		else
			cout << "\nClient was NOT found :-(\n";

		printClient(foundedClient);
	}
};

