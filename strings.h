#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class strings
{
private:
	string _value;

public:
	strings() : _value("") {}
	strings(string value) : _value(value) {}

	string getValue() const
	{
		return _value;
	}
	void setValue(const string& value)
	{
		_value = value;
	}

	__declspec(property(get = getValue, put = setValue)) string value;



	// ==============================================================================
	// ===================== Functions To Operation With Strings ====================
	// ==============================================================================

	void printInitials(const string& text)
	{
		cout << text[0] << endl;

		for (int i = 1; i < text.length() - 1; i++)
		{
			if (text[i] == ' ' && text[i + 1] != ' ')
				cout << text[i + 1] << endl;
		}
	} void printInitials() { printInitials(_value); }


	char upper(char letter)
	{

		if (letter >= 97 && letter <= 122)
			return char(letter - 32);
		else
			return letter;

	}
	char lower(char letter)
	{

		if (letter >= 65 && letter <= 90)
			return char(letter + 32);
		else
			return letter;

	}


	void capitalize(string& word)
	{
		bool firstLetter = true;

		for (int i = 0; i < word.length(); i++)
		{
			if (word[i] != ' ' && firstLetter)
				word[i] = upper(word[i]);

			firstLetter = (word[i] == ' ' ? true : false);
		}
	} void capitalize() { capitalize(_value); }


	void decapitalize(string& word)
	{
		bool firstLetter = true;

		for (int i = 0; i < word.length(); i++)
		{
			if (word[i] != ' ' && firstLetter)
				word[i] = lower(word[i]);

			firstLetter = (word[i] == ' ' ? true : false);
		}
	} void decapitalize() { decapitalize(_value); }


	string lowercase(string& word)
	{
		for (int letter = 0; letter < word.length(); letter++)
		{
			if (word[letter] >= 65 && word[letter] <= 90)
				word[letter] += 32;
		}
	} string lowercase() { lowercase(_value); }


	static string uppercase(string text)
	{
		for (char& c : text)
		{
			c = toupper(c);
		}
		return text;
	} string uppercase() { return uppercase(_value); }


	char invertCharCase(char letter)
	{
		if (letter >= 65 && letter <= 90)
			letter += 32;

		else if (letter >= 97 && letter <= 122)
			letter -= 32;

		return letter;
	}


	string invertcase(string& word)
	{
		for (int i = 0; i < word.length(); i++)
		{
			word[i] = invertCharCase(word[i]);
		}
	} string invertcase() { invertcase(_value); }


	int count_letters(const string& word, char letter, bool matchCase = true)
	{
		int counter = 0;

		for (int i = 0; i < word.length(); i++)
		{
			switch (matchCase)
			{
			case true:
				if (word[i] == letter)
					counter++;
				break;
			case false:
				if (lower(word[i]) == lower(letter))
					counter++;
				break;
			}
		}

		return counter;
	} int count_letters(char letter, bool matchCase = true) { return count_letters(_value, letter, matchCase); }


	int count_words(string& text)
	{
		string delimeter = " ";
		int counter = 0;
		short pos = 0;
		string sWord;

		while ((pos = text.find(delimeter)) != string::npos)
		{
			sWord = text.substr(0, pos);

			if (sWord != "")
				counter++;

			text.erase(0, pos + delimeter.length());
		}

		if (text != "")
			counter++;

		return counter;
	} int count_words() { return count_words(_value); }


	static vector<string> split(string& text, string delimeter = " ")
	{
		short pos = 0;
		string sWord;

		vector<string> vWords;

		while ((pos = text.find(delimeter)) != string::npos)
		{
			sWord = text.substr(0, pos);

			if (sWord != "")
				vWords.push_back(sWord);

			text.erase(0, pos + delimeter.length());
		}

	
		vWords.push_back(text);

		return vWords;
	} vector<string> split() { return split(_value); }


	string ltrim(const string& s)
	{
		size_t i = 0;
		while (i < s.length() && s[i] == ' ')
			i++;

		return s.substr(i);
	}

	string rtrim(const string& s)
	{
		if (s.empty()) return "";

		int i = s.length() - 1;
		while (i >= 0 && s[i] == ' ')
			i--;

		return s.substr(0, i + 1);
	}

	string trim(const string& s)
	{
		return ltrim(rtrim(s));
	}



	static string join(vector<string> words, string delimiter)
	{
		string joinedString = "";

		for (string& word : words)
		{
			joinedString += (word + delimiter);
		}

		return joinedString.substr(0, joinedString.length() - delimiter.length());
	}


	string replace(string& sen, string orgWord, string desWord, bool match = false)
	{
		if (match) sen = lowercase(sen);

		vector<string> vWords = split(sen);

		for (string& word : vWords)
		{
			if (word == orgWord) word = desWord;
		}

		sen = join(vWords, " ");
	} string replace(string orgWord, string desWord, bool match = false) { replace(_value, orgWord, desWord, match); }
};