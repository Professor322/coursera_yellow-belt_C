//
// Created by professor on 4/7/20.
//
#include <string>
#include <iostream>

using namespace std;

class INotifier {
public:
	virtual void Notify(const string& me) const  = 0;
};

class SmsNotifier : public INotifier {
public:
	SmsNotifier(const string& tel_number) : _tel_number(tel_number) {}

	void Notify(const string& me) const override {
		SendSms(_tel_number, me);
	}

private:
	const string _tel_number;
};

class EmailNotifier : public INotifier {
public:
	EmailNotifier(const string& email_address) : _email_address(email_address) {}

	void Notify(const string& me) const override {
		SendEmail(_email_address, me);
	}
private:
	const string _email_address;
};


