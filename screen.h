#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "user.h"
#include "global.h"
#include "date.h"

using namespace std;

class screen
{

protected:
	static void _printHeader(string title, string subTitle = "")
	{
		cout << setw(27) << "" << "--------------------------------------\n";
		cout << "\t\t\t\t      " << title << endl;
		if (subTitle != "")
			cout << "\t\t\t\t      " << subTitle << endl;
		cout << setw(27) << "" << "--------------------------------------\n";
		cout << right << setw(33) << " User: " << currentUser.username << endl;
		date d;
		cout << right << setw(33) << " Date: " << date::toString(date()) << endl << endl;
	}

	static bool checkRights (int perm)
	{
		if (!currentUser.checkPermissions(perm))
		{
			cout << left << setw(27) << "" << "-----------------------------------------\n";
			cout << "\t\t\t\t" << "Access Denied! Contact your admin." << endl;
			cout << left << setw(27) << "" << "-----------------------------------------\n";
			return false;
		}
		else
			return true;
	}
};

