//
// Created by professor on 4/29/20.
//
#pragma once

#include "includes.h"

using namespace std;

struct Date {
	int year;
	int month;
	int day;

};

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

ostream& operator<<(ostream& os, const Date& date);

Date ParseDate(istream& is);