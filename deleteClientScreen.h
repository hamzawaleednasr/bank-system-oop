#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "client.h"
#include "inputValidate.h"

using namespace std;

class deleteClientScreen : protected screen
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
	static void deleteClient()
	{

		if (!checkRights(user::stPermisions::DELETE))
			return;

		_printHeader("Delete Client Screen");

		cout << "Enter the account number: ";
		string accountNumber = inputValidate::readString();

		while (!client::isClientExist(accountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accountNumber = inputValidate::readString();
		}

		client deleteClient = client::find(accountNumber);
		printClient(deleteClient);

		cout << "\nAre you sure you want to delete this client [y/n]: ";
		char wantToDelete = 'n';
		cin >> wantToDelete;

		if (wantToDelete == 'Y' || wantToDelete == 'y')
		{
			if (deleteClient.deleteClient())
				cout << "\nClient deleted successfully :-)\n";
			else
				cout << "\nError Client was not deleted!\n";
		}
	}
};

