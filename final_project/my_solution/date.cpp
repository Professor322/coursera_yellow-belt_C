//
// Created by professor on 4/29/20.
//
#include "includes.h"
#include "date.h"

bool operator!=(const Date &lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) !=
			tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date &lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) ==
		   tie(rhs.year, rhs.month, rhs.day);
}

bool operator>(const Date &lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) >
		   tie(rhs.year, rhs.month, rhs.day);
}

bool operator>=(const Date &lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) >=
		   tie(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Date &lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) <
		   tie(rhs.year, rhs.month, rhs.day);
}

bool operator<=(const Date &lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) <=
		   tie(rhs.year, rhs.month, rhs.day);
}

ostream& operator<<(ostream& os, const Date& date) {
	os << setfill('0') << setw(4) << date.year << "-"
	                      << setw(2) << date.month << "-"
	                      << setw(2) << date.day;
	return os;
}

Date ParseDate(istream& is) {
	int year, month, day;

	is >> year;
	is.get();
	is >> month;
	is.get();
	is >> day;
	return {year, month, day};
}

