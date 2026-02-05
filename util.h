#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "date.h"

using namespace std;

class util
{
public:
	enum charsType
	{
		small = 1,
		capital,
		special,
		digit,
		mix
	};

	static void srand()
	{
		std::srand((unsigned)time(NULL));
	}

	static int randomNumber(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}

	static string encryption(string originalText, int encryptionKey)
	{
		string encryptedText = "";

		for (int i = 0; i < originalText.length(); i++)
			encryptedText += char((int)originalText[i] + encryptionKey);

		return encryptedText;
	}

	static string decryption(string encryptedText, int encryptionKey)
	{
		string decryptedText = "";

		for (int i = 0; i < encryptedText.length(); i++)
			decryptedText += char((int)encryptedText[i] - encryptionKey);

		return decryptedText;
	}

	static char getRandomCharacter(charsType type)
	{
		switch (type)
		{
		case charsType::small:
			return randomNumber(97, 122);
		case charsType::capital:
			return randomNumber(65, 90);
		case charsType::special:
			return randomNumber(33, 38);
		case charsType::digit:
			return randomNumber(48, 57);
		case charsType::mix:
			return getRandomCharacter((charsType)randomNumber(1, 4));
		}
	}

	static string generateWord(charsType type, int length)
	{
		string word;

		for (int i = 1; i <= length; i++)
		{
			word += getRandomCharacter(type);
		}

		return word;
	}

	static string generateKey(charsType type)
	{
		string key;

		for (int i = 1; i <= 4; i++)
		{
			key += generateWord(type, 4);
			if (i != 4)
				key += "-";
		}

		return key;
	}

	static void generateKeys(charsType type, int numOfKeys)
	{
		for (int i = 1; i <= numOfKeys; i++)
		{
			cout << "Key [" << i << "]: " << generateKey(type) << endl;
		}
	}

	static void fillArrayWithRandomNumbers(int arr[], int length, int from, int to)
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = randomNumber(from, to);
		}
	}

	static void fillArrayWithRandomWords(string arr[], int length, charsType type)
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = generateWord(type, 4);
		}
	}

	static void fillArrayWithRandomKeys(string arr[], int length, charsType type)
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = generateKey(type);
		}
	}

	static void swap(int& a, int& b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	static void swap(double& a, double& b)
	{
		double temp = a;
		a = b;
		b = temp;
	}

	static void swap(bool& a, bool& b)
	{
		bool temp = a;
		a = b;
		b = temp;
	}

	static void swap(char& a, char& b)
	{
		char temp = a;
		a = b;
		b = temp;
	}

	static void swap(string& a, string& b)
	{
		string temp = a;
		a = b;
		b = temp;
	}

	static void swap(date& a, date& b)
	{
		date temp = a;
		a = b;
		b = temp;
	}

	static void shuffleArray(int arrayOfNumbers[100], int elementsOfArray)
	{
		for (int i = 0; i < elementsOfArray; i++)
			swap(arrayOfNumbers[randomNumber(1, elementsOfArray) - 1], arrayOfNumbers[randomNumber(1, elementsOfArray) - 1]);
	}

	static void shuffleArray(string arrayOfNumbers[100], int elementsOfArray)
	{
		for (int i = 0; i < elementsOfArray; i++)
			swap(arrayOfNumbers[randomNumber(1, elementsOfArray) - 1], arrayOfNumbers[randomNumber(1, elementsOfArray) - 1]);
	}

	static string convertBelow1000(int num)
	{
		string ones[] = {
			"zero","one","two","three","four","five","six",
			"seven","eight","nine","ten","eleven","twelve",
			"thirteen","fourteen","fifteen","sixteen",
			"seventeen","eighteen","nineteen"
		};

		string tens[] = {
			"","", "twenty","thirty","forty",
			"fifty","sixty","seventy","eighty","ninety"
		};

		string result = "";

		if (num >= 100) {
			result += ones[num / 100] + " hundred";
			num %= 100;
			if (num > 0)
				result += " and ";
		}

		if (num >= 20) {
			result += tens[num / 10];
			if (num % 10 != 0)
				result += " " + ones[num % 10];
		}
		else if (num > 0) {
			result += ones[num];
		}

		return result;
	}

	static string numberToWords(long long num)
	{
		if (num == 0)
			return "zero";

		string result = "";

		if (num >= 1'000'000'000) {
			result += convertBelow1000(num / 1'000'000'000) + " billion ";
			num %= 1'000'000'000;
		}

		if (num >= 1'000'000) {
			result += convertBelow1000(num / 1'000'000) + " million ";
			num %= 1'000'000;
		}

		if (num >= 1000) {
			result += convertBelow1000(num / 1000) + " thousand ";
			num %= 1000;
		}

		if (num > 0)
			result += convertBelow1000(num);

		return result;
	}
};
