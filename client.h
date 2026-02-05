#pragma once

#include <vector>
#include<string>
#include <fstream>
#include "person.h"
#include "strings.h"

class client : public person
{
private:
	enum enObjMode { empty, update, add };
	enObjMode _mode;
	string _accountNumber = "", _pin = "";
	double _balance = 0;
	bool _deleteMark = false;
	
	struct stTransferLog;

	static client _convertLineToClient(string line, string separetor = "#//#")
	{
		vector<string> clientInfo = strings::split(line, separetor);

		return client(enObjMode::update, clientInfo[0], clientInfo[1], clientInfo[2], clientInfo[3], clientInfo[4], clientInfo[5], stod(clientInfo[6]));
	}

	static stTransferLog _convertLineToTransfer(string line, string separetor = "#//#")
	{
		vector<string> transfer = strings::split(line, separetor);

		return stTransferLog(transfer[0], transfer[1], transfer[2], stod(transfer[3]), transfer[4], transfer[5], transfer[6]);
	}

	static string _convertClientToLine(client client, string separator = "#//#")
	{
		return client.firstName + separator + client.lastName + separator + client.email + separator + 
			client.phoneNumber + separator + client.accountNumber + separator + client.pin + separator + to_string(client.balance);
	}

	static vector<client> _loadClientsFromFile()
	{
		vector<client> clients;
		string line = "";

		std::fstream file;
		file.open("clients.txt", ios::in);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				clients.push_back(_convertLineToClient(line));
			}
		}

		return clients;
	}

	static vector<stTransferLog> _loadTransfersFromFile()
	{
		vector<stTransferLog> transfers;
		string line = "";

		std::fstream file;
		file.open("transferLog.txt", ios::in);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				transfers.push_back(_convertLineToTransfer(line));
			}
		}

		return transfers;
	}

	static void _appendToFile(const string& line)
	{
		fstream file;
		file.open("clients.txt", ios::app);

		if (file.is_open())
			file << line << endl;
	}

	static void _saveClientsInFile(vector<client>& clients)
	{
		fstream file;
		file.open("clients.txt", ios::out);

		if (file.is_open())
		{
			for (client& client : clients)
			{
				if (!client._deleteMark)
				{
					file << _convertClientToLine(client) << std::endl;
				}
			}
		}
	}

	void _update()
	{
		vector<client> _vClients = _loadClientsFromFile();

		for (client& c : _vClients)
		{
			if (c.accountNumber == _accountNumber)
			{
				c = *this;
				break;
			}
		}

		_saveClientsInFile(_vClients);
	}

	void _add()
	{
		_appendToFile(_convertClientToLine(*this));
	}

	static client _getEmptyClient()
	{
		return client(enObjMode::empty, "", "", "", "", "", "", 0);
	}

public:
	client(enObjMode mode, string fname, string lname, string email, string phone, string accNum, string pin, double balance)
		: person(fname, lname, email, phone),
		_mode(mode), _accountNumber(accNum), _pin(pin), _balance(balance)
	{}

	// ---- Getters & Setters
	string getAccountNumber()
	{
		return _accountNumber;
	}
	string getPIN()
	{
		return _pin;
	}
	double getBalance()
	{
		return _balance;
	}

	void setPIN(string pin)
	{
		_pin = pin;
	}
	void setBalance(double balance)
	{
		_balance = balance;
	}

	__declspec(property(get = getAccountNumber)) string accountNumber;
	__declspec(property(get = getPIN, put = setPIN)) string pin;
	__declspec(property(get = getBalance, put = setBalance)) double balance;


	struct stTransferLog {
		string dateTime;
		string sAcc;
		string dAcc;
		double amount;
		string sBalance;
		string dBalance;
		string username;
	};

	bool isEmpty()
	{
		return _mode == enObjMode::empty;
	}

	static client find(string accountNumber)
	{
		fstream file;
		file.open("clients.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				client currentClient = _convertLineToClient(line);

				if (currentClient.accountNumber == accountNumber)
				{
					file.close();
					return currentClient;
				}
			}
			file.close();
		}

		return _getEmptyClient();
	}

	static client find(string accountNumber, string pin)
	{
		fstream file;
		file.open("clients.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				client currentClient = _convertLineToClient(line);

				if (currentClient.accountNumber == accountNumber && currentClient.pin == pin)
				{
					file.close();
					return currentClient;
				}
			}
			file.close();
		}

		return _getEmptyClient();
	}

	enum enSaveStates { failedEmptyObject, success, failedAccountNumberExists };

	enSaveStates save()
	{
		switch (_mode)
		{
		case enObjMode::empty:
			return enSaveStates::failedEmptyObject;
		case enObjMode::update:
			_update();
			return enSaveStates::success;
		case enObjMode::add:
			if (isClientExist(_accountNumber))
				return enSaveStates::failedAccountNumberExists;
			else 
			{
				_add();
				_mode = enObjMode::update;
				return enSaveStates::success;
			}

		}
	}

	static bool isClientExist(const string& accountNumber)
	{
		client test_client = client::find(accountNumber);
		return (!test_client.isEmpty());
	}

	static client getAddNewClientObject(string accountNumber)
	{
		return client(enObjMode::add, "", "", "", "", accountNumber, "", 0);
	}

	bool deleteClient()
	{
		vector<client> _vClients = _loadClientsFromFile();

		for (client& c : _vClients)
		{
			if (c.accountNumber == _accountNumber)
			{
				c._deleteMark = true;
			}
		}

		_saveClientsInFile(_vClients);

		*this = _getEmptyClient();

		return true;
	}

	static vector<client> getClientsList()
	{
		return _loadClientsFromFile();
	}

	static vector<stTransferLog> getTransfersList()
	{
		return _loadTransfersFromFile();
	}

	static double getTotalBalances()
	{
		vector<client> clients = _loadClientsFromFile();
		double total = 0;

		for (client& c : clients)
			total += c.balance;

		return total;
	}

	void deposite(double amount)
	{
		_balance += amount;
		save();
	}

	void withdraw(double amount)
	{
		_balance -= amount;
		save();
	}
};

