#pragma once

#include "screen.h"
#include "client.h"
#include "date.h"
#include "inputValidate.h"
#include <string>

class transferScreen : protected screen
{
private:
	static void _printClient(client c)
	{
		cout << "\nClient Card:\n";
		cout << "-----------------------\n";
		cout << "Full Name: " << c.fullName() << endl;
		cout << "Account Number: " << c.accountNumber << endl;
		cout << "Balance: " << c.balance << endl;
		cout << "-----------------------\n";
	}

	static client _getClient()
	{
		string accNumber = inputValidate::readString();

		while (!client::isClientExist(accNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accNumber = inputValidate::readString();
		}

		return client::find(accNumber);
	}

	static double _readTransferAmount(client c)
	{
		double amount = inputValidate::readDouble("\nEnter transfer amount: ");

		while (amount > c.balance)
		{
			cout << "\nAmount exceeds the balance, try another amount: ";
			amount = inputValidate::readDouble("");
		}

		return amount;
	}

	static string _getTransferLine(client from, client to, double amount, string separator = "#//#")
	{
		return date::getTimeNow() + separator +
			from.accountNumber + separator +
			to.accountNumber + separator +
			to_string(from.balance) + separator +
			to_string(to.balance) + separator +
			to_string(amount) + separator +
			currentUser.username;
	}

	static void _appendToFile(const string& line)
	{
		fstream file;
		file.open("transferLog.txt", ios::app);

		if (file.is_open())
			file << line << endl;
	}

	static void _recordNewTransfer(client from, client to, double amount)
	{
		_appendToFile(_getTransferLine(from, to, amount));
	}

public:
	static void showTransferScreen()
	{
		_printHeader("Transfer Screen");

		cout << "\nEnter account number to transfer from: ";
		client from = _getClient();

		_printClient(from);

		cout << "\nEnter account number to transfer to: ";
		client to = _getClient();

		_printClient(to);

		double amount = _readTransferAmount(from);

		char transApply = 'n';
		cout << "\nAre you sure to do this transfer? [y/n]: ";
		cin >> transApply;

		if (transApply == 'Y' || transApply == 'y')
		{
			from.withdraw(amount);
			to.deposite(amount);

			_recordNewTransfer(from, to, amount);
			cout << "\nTransfer done successfully! :-)\n";
		}

	}

};

