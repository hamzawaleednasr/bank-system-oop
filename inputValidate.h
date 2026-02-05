#pragma once

#include "date.h"
#include <iostream>
#include <limits>

using namespace std;

class inputValidate
{
public:
	static bool isNumberBetween(int number, int start, int end)
	{
		return number > start && number < end;
	}

	static bool isDateBetween(date d, date start, date end)
	{
		return date::isDate1BeforeDate2(start, d) && date::isDate1BeforeDate2(d, end);
	}

	static bool isDateValid(date date)
	{
		return (date.month <= 12 && date.month >= 1) && (date.day <= date::numberOfDaysInMonth(date.year, date.month) && date.day >= 1);
	}

	static int readInt(string message = "Enter a number: ")
	{
		int number;

		cout << message;

		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid number!, enter valid number: ";
		}

		return number;
	}

	static double readDouble(string message = "Enter a number: ")
	{
		double number;

		cout << message;

		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid number!, enter valid number: ";
		}

		return number;
	}

	static string readString()
	{
		string text;
		getline(cin >> ws, text);
		return text;
	}

	static int readIntInRange(int from, int to, string message = "Enter a number: ")
	{
		int number;

		number = readInt(message);

		while (number < from || number > to)
		{
			cout << "Please enter number between [" << from << "-" << to << "]: ";
			number = readInt("");
		}

		return number;
	}

	static double readDoubleInRange(double from, double to)
	{
		double number;

		number = readDouble();

		while (number < from || number > to)
		{
			cout << "Please enter number between [" << from << "-" << to << "]: ";
			number = readDouble("");
		}

		return number;
	}
};
