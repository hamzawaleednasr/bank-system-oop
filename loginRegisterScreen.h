#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "screen.h"
#include "user.h"
#include "util.h"

using namespace std;

class loginRegisterScreen : protected screen
{
private:
	static void printRegister(user::stLoginRegister& r)
	{
		cout << "| " << setw(25) << left << r.dateTime;
		cout << "| " << setw(20) << left << r.username;
		cout << "| " << setw(20) << left << util::decryption(r.password, 1026);
		cout << "| " << setw(15) << left << r.perm << endl;
	}

public:
	static void showRegisters()
	{

		if (!checkRights(user::stPermisions::LOGIN_REGISTER))
			return;

		vector<user::stLoginRegister> registers = user::getRegistersList();

		_printHeader("Login Register List Screen", "  (" + to_string(registers.size()) + ") Register(s).");

		cout << "------------------------------------------------------------------------------------------------------\n";
		cout << "| " << left << setw(25) << "Date / Time" << "| " << left << setw(20) << "Username" << "| " << left << setw(20) << "Password" << "| " << left << setw(15) << "Permissions" << endl;
		cout << "------------------------------------------------------------------------------------------------------\n";

		if (registers.size() == 0)
			cout << "\nThere are no records.\n";
		else
			for (user::stLoginRegister & r : registers)
				printRegister(r);

		cout << "------------------------------------------------------------------------------------------------------\n";
	}
};

