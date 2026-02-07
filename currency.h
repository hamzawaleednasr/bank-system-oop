#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "strings.h"

class currency
{
private:
	enum enObjMode { empty, update };
	enObjMode _mode;

	string _country;
	string _code;
	string _currencyName;
	float _rate;

	static currency _convertLineToCurrency(string line, string separetor = "#//#")
	{
		vector<string> currencyInfo = strings::split(line, separetor);

		return currency(enObjMode::update, currencyInfo[0], currencyInfo[1], currencyInfo[2], stof(currencyInfo[3]));
	}

	static string _convertCurrencyToLine(currency currency, string separator = "#//#")
	{
		return currency._country + separator + currency._code + separator + currency._currencyName + separator +
			to_string(currency._rate);
	}

	static vector<currency> _loadCurrenciesFromFile()
	{
		vector<currency> currencies;
		string line = "";

		std::fstream file;
		file.open("currencies.txt", ios::in);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				currencies.push_back(_convertLineToCurrency(line));
			}
		}

		return currencies;
	}

	static void _appendToFile(const string& line)
	{
		fstream file;
		file.open("currencies.txt", ios::app);

		if (file.is_open())
			file << line << endl;
	}

	static void _saveCurrenciesInFile(vector<currency>& currencies)
	{
		fstream file;
		file.open("currencies.txt", ios::out);

		if (file.is_open())
		{
			for (currency& currency : currencies)
			{
				file << _convertCurrencyToLine(currency) << std::endl;
			}
		}
	}

	void _update()
	{
		vector<currency> currencies = _loadCurrenciesFromFile();

		for (currency& c : currencies)
		{
			if (c._code == _code)
			{
				c = *this;
				break;
			}
		}

		_saveCurrenciesInFile(currencies);
	}

	static currency _getEmptyCurrency()
	{
		return currency(enObjMode::empty, "", "", "", 0);
	}

public:
	currency(enObjMode mode, string country, string code, string currencyName, float rate)
		: _mode(mode), _country(country), _code(code), _currencyName(currencyName), _rate(rate)
	{
	}


	// ======= Getters & Setters =======
	string getCountry()
	{
		return _country;
	}
	string getCode()
	{
		return _code;
	}
	string getCurrencyName()
	{
		return _currencyName;
	}
	float getRate()
	{
		return _rate;
	}

	void updateRate(float newRate)
	{
		_rate = newRate;
		_update();
	}

	bool isEmpty()
	{
		return _mode == enObjMode::empty;
	}

	static currency find(string codeOrCountry)
	{
		fstream file;
		file.open("currencies.txt", ios::in);

		string keyword = strings::uppercase(codeOrCountry);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				currency currentCurrency = _convertLineToCurrency(line);

				if (currentCurrency._code == keyword || strings::uppercase(currentCurrency._country) == keyword)
				{
					file.close();
					return currentCurrency;
				}
			}
			file.close();
		}

		return _getEmptyCurrency();
	}

	static bool isCurrencyExist(const string& codeOrCountry)
	{
		currency test_currency = currency::find(codeOrCountry);
		return (!test_currency.isEmpty());
	}

	static vector<currency> getCurrenciesList()
	{
		return _loadCurrenciesFromFile();
	}
};

