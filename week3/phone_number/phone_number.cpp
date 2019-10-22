//
// Created by professor on 22.10.19.
//

#include "phone_number.h"
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iostream>
/*
PhoneNumber::PhoneNumber(const string& international_number) {
	istringstream is(international_number);

	char sign = is.get();
	getline(is, country_code_, '-');
	getline(is, city_code_, '-');
	getline(is, local_number_);

	if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
		throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
	}
}*/

PhoneNumber::PhoneNumber(const string &international_number) {

	if (international_number[0] != '+'||
		count(international_number.begin(), international_number.end(), '-') < 2
		) {
		throw invalid_argument("wrong format: " + international_number);
	}
	istringstream ss(international_number);
	ss.ignore(1);
	getline(ss, country_code_, '-');
	getline(ss, city_code_, '-');
	getline(ss, local_number_);
	if (country_code_.empty() ||
		city_code_.empty() ||
		local_number_.empty()) {
		throw invalid_argument("wrong format: " + international_number);
	}
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}
/*
int 	main() {
	PhoneNumber pn("+--");

	cout << pn.GetCountryCode() << endl;
	cout << pn.GetCityCode() << endl;
	cout << pn.GetLocalNumber() << endl;
	cout << pn.GetInternationalNumber() << endl;
	return 0;
}*/