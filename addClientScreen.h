#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "client.h"
#include "inputValidate.h"

class addClientScreen : protected screen
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
	static void addNewClient()
	{

		if (!checkRights(user::stPermisions::ADD))
			return;

		_printHeader("Add New Client Screen");

		cout << "Enter the account number: ";
		string accountNumber = inputValidate::readString();

		while (client::isClientExist(accountNumber))
		{
			cout << "\nAccount number is already in use, choose another one: ";
			accountNumber = inputValidate::readString();
		}

		client newClient = client::getAddNewClientObject(accountNumber);
		cout << "\nCreate New Client:";
		cout << "\n----------------------------";
		readClientInfo(newClient);

		client::enSaveStates result = newClient.save();

		switch (result)
		{
		case client::enSaveStates::success:
			cout << "\nAccount Added Successfully :-)\n";
			printClient(newClient);
			break;
		case client::enSaveStates::failedEmptyObject:
			cout << "\nError account was not saved because it's Empty";
			break;
		case client::enSaveStates::failedAccountNumberExists:
			cout << "\nError account was not saved because account number is used!\n";
			break;
		}
	}
};

