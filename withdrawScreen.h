#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "client.h"
#include "inputValidate.h"

using namespace std;

class withdrawScreen : protected screen
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

	static double _readWithdrawAmount(client c)
	{
		double amount = inputValidate::readDouble("Enter amount to withdraw: ");

		while (amount > c.balance)
		{
			cout << "\nAmount exceeds the balance, try another amount: ";
			amount = inputValidate::readDouble("");
		}

		return amount;
	}

public:
	static void showWithdrawScreen()
	{

		_printHeader("Withdraw Screen");

		cout << "Enter the account number: ";
		string accountNumber = inputValidate::readString();

		while (!client::isClientExist(accountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accountNumber = inputValidate::readString();
		}

		client client1 = client::find(accountNumber);
		printClient(client1);

		cout << "\nAre you sure you want to withdraw from this client [y/n]: ";
		char wantToWithdraw = 'n';
		cin >> wantToWithdraw;

		if (wantToWithdraw == 'Y' || wantToWithdraw == 'y')
		{
			double amount = _readWithdrawAmount(client1);
			client1.withdraw(amount);
			cout << "\nThe transation has been done successfully! :-)\n";

			cout << "\nThe new balance is: " << client1.balance << endl;
		}
		else
			cout << "\nTransaction has been canceled.\n";
	}
};