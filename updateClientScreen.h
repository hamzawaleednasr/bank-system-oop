#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "client.h"
#include "inputValidate.h"

class updateClientScreen : protected screen
{
private:
	static void readClientInfo(client& client)
	{
		cout << "\nEnter first name: ";
		client.firstName = inputValidate::readString();

		cout << "Enter last name: ";
		client.lastName = inputValidate::readString();

		cout << "Enter email: ";
		client.email = inputValidate::readString();

		cout << "Enter phone number: ";
		client.phoneNumber = inputValidate::readString();

		cout << "Enter PIN: ";
		client.pin = inputValidate::readString();

		client.balance = inputValidate::readDouble("Enter balance: ");
	}

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
	static void updateClient()
	{

		if (!checkRights(user::stPermisions::UPDATE))
			return;

		_printHeader("Update Client Screen");

		cout << "Enter the account number: ";
		string accountNumber = inputValidate::readString();

		while (!client::isClientExist(accountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accountNumber = inputValidate::readString();
		}

		client toUpdateClient = client::find(accountNumber);
		printClient(toUpdateClient);

		cout << "\nAre you sure you want to update this client [y/n]: ";
		char wantToDelete = 'n';
		cin >> wantToDelete;

		if (wantToDelete == 'Y' || wantToDelete == 'y')
		{
			cout << "\n\nUpdate Info:\n";
			cout << "-------------------------";
			readClientInfo(toUpdateClient);

			client::enSaveStates result = toUpdateClient.save();

			switch (result)
			{
			case client::enSaveStates::success:
				cout << "\nAccount Updated Successfully :-)\n";
				printClient(toUpdateClient);
				break;
			case client::enSaveStates::failedEmptyObject:
				cout << "\nError account was not saved because it's Empty";
				break;
			}
		}
	}
};

