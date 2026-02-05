#pragma once

#include <iostream>
#include <string>
#include "screen.h"
#include "client.h"
#include "util.h"

using namespace std;

class totalBalancesScreen : protected screen
{
private:
	static void _printBalance(client& c)
	{
		cout << "| " << setw(20) << left << c.accountNumber;
		cout << "| " << setw(50) << left << c.fullName();
		cout << "| " << setw(20) << left << c.balance << endl;
	}

public:
	static void showTotalBalancesScreen()
	{

		_printHeader("Total Balances Screen");

		vector<client> clients = client::getClientsList();

		cout << "\t\t\t   Client List (" << clients.size() << ") Client(s)." << endl;
		cout << "------------------------------------------------------------------------------------------------------\n";
		cout << "| " << left << setw(20) << "Account Number" << "| " << left << setw(50) << "Full Name" << "| " << left << setw(20) << "Balance" << endl;
		cout << "------------------------------------------------------------------------------------------------------\n";

		if (clients.size() == 0)
			cout << "\nThere are no clients.\n";
		else
			for (client& c : clients)
				_printBalance(c);

		cout << "------------------------------------------------------------------------------------------------------\n";

		double total = client::getTotalBalances();

		cout << "\t\t\t\t\t\tTotal Balances: " << total << endl;
		cout << "\t\t\t\t\t\t(" << util::numberToWords(total) << ")" << endl;
	}
};