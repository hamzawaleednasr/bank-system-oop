#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "screen.h"
#include "client.h"

using namespace std;

class clientListScreen : protected screen
{
private:
	static void printClient(client& c)
	{
		cout << "| " << setw(15) << left << c.accountNumber;
		cout << "| " << setw(20) << left << c.fullName();
		cout << "| " << setw(15) << left << c.phoneNumber;
		cout << "| " << setw(10) << left << c.pin;
		cout << "| " << setw(12) << left << c.balance << endl;
	}

public:
	static void showClients()
	{

		if (!checkRights(user::stPermisions::LIST))
			return;

		vector<client> clients = client::getClientsList();

		_printHeader("Client List Screen", "  (" + to_string(clients.size()) + ") Client(s).");

		cout << "------------------------------------------------------------------------------------------------------\n";
		cout << "| " << left << setw(15) << "Account Number" << "| " << left << setw(20) << "Full Name" << "| " << left << setw(15) << "Phone Number" << "| " << left << setw(10) << "PIN" << "| " << left << std::setw(12) << "Balance" << endl;
		cout << "------------------------------------------------------------------------------------------------------\n";

		if (clients.size() == 0)
			cout << "\nThere are no clients.\n";
		else
			for (client& c : clients)
				printClient(c);

		cout << "------------------------------------------------------------------------------------------------------\n";
	}
};

