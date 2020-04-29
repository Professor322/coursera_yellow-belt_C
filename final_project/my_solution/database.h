//
// Created by professor on 4/29/20.
//
#pragma once

#include "includes.h"
#include "date.h"

using namespace std;


class Database {
public:
	using Event = string;
	struct UniqueEvents {
		set<Event> unique;
		vector<Event> order;
	};

	void Add(const Date& date, const Event& event);
	void Print(ostream& is) const;

	int RemoveIf(function<bool(const Date&, const string&)> p);

	list<pair<Date, Event>> FindIf(function<bool(const Date&, const string&)> p) const;

	pair<Date, Event> Last(const Date& date) const;
private:
	map<Date, UniqueEvents> date_to_event;
};



ostream& operator<<(ostream& os, const pair<Date, string>& value);
