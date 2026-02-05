#pragma once

#include <string>

using namespace std;

class person
{
private:
	string _firstName, _lastName, _email, _phoneNumber;

public:
	// Constructor
	person(string fname, string lname, string email, string phone) 
		: _firstName(fname), _lastName(lname), _email(email), _phoneNumber(phone)
	{}

	// ================================================
	// =============== Getter & Setters ===============
	// ================================================
	// ----- Getters -----
	string getFirstName()
	{
		return _firstName;
	}
	string getLastName()
	{
		return _lastName;
	}
	string getEmail()
	{
		return _email;
	}
	string getPhoneNumber()
	{
		return _phoneNumber;
	}

	// ----- Setters -----
	void setFirstName(string fname)
	{
		_firstName = fname;
	}
	void setLastName(string lname)
	{
		_lastName = lname;
	}
	void setEmail(string email)
	{
		_email = email;
	}
	void setPhoneNumber(string phone)
	{
		_phoneNumber = phone;
	}

	__declspec(property(get = getFirstName, put = setFirstName)) string firstName;
	__declspec(property(get = getLastName, put = setLastName)) string lastName;
	__declspec(property(get = getEmail, put = setEmail)) string email;
	__declspec(property(get = getPhoneNumber, put = setPhoneNumber)) string phoneNumber;

	string fullName()
	{
		return _firstName + " " + _lastName;
	}
};

