#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "screen.h"
#include "client.h"

using namespace std;

class transferLogScreen : protected screen
{
private:
	static void printTransfer(client::stTransferLog& t)
	{
		cout << "| " << setw(20) << left << t.dateTime;
		cout << "| " << setw(10) << left << t.sAcc;
		cout << "| " << setw(10) << left << t.dAcc;
		cout << "| " << setw(15) << left << t.sBalance;
		cout << "| " << setw(15) << left << t.dBalance;
		cout << "| " << setw(10) << left << t.amount;
		cout << "| " << setw(10) << left << t.username << endl;
	}

public:
	static void showTransfers()
	{

		vector<client::stTransferLog> transfers = client::getTransfersList();

		_printHeader("Transfer Log List Screen", "  (" + to_string(transfers.size()) + ") Transfer(s).");

		cout << "------------------------------------------------------------------------------------------------------\n";
		cout << "| " << left << setw(20) << "Date / Time" << "| " << left << setw(10) << "s.Acc" << "| " << left << setw(10) << "d.Acc" << "| " << left << setw(15) << "s.Balance" << "| " << left << setw(15) << "d.Balance" << "| " << left << setw(10) << "amount" << "| " << left << setw(10) << "username" << endl;
		cout << "------------------------------------------------------------------------------------------------------\n";

		if (transfers.size() == 0)
			cout << "\nThere are no records.\n";
		else
			for (client::stTransferLog& t : transfers)
				printTransfer(t);

		cout << "------------------------------------------------------------------------------------------------------\n";
	}
};

