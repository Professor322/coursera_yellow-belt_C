//
// Created by professor on 4/29/20.
//

#include "database.h"


ostream& operator<<(ostream& os, const pair<Date, string>& value) {
	os << value.first << " " << value.second;
	return os;
}

void Database::Add(const Date &date, const Event &event) {
	auto& certain_date = date_to_event[date];

	if (!certain_date.unique.count(event)) {
		certain_date.unique.insert(event);
		certain_date.order.push_back(event);
	}
}

pair<Date, string> Database::Last(const Date &date) const {
	auto it = date_to_event.lower_bound(date);
	if (it != date_to_event.end() && it->first == date) {
		return {it->first, it->second.order.back()};
	}
	if (it != date_to_event.begin()) {
		auto pr_it = prev(it);
		return {pr_it->first, pr_it->second.order.back()};
	}
	throw invalid_argument("");
}

void Database::Print(ostream &is) const {
	for (const auto& [date, events] : date_to_event) {
		for (const auto& event : events.order) {
			is << date << " " << event << endl;
		}
	}
}

list<pair<Date, string> > Database::FindIf(function<bool(const Date&, const string&)> p) const {
	list<pair<Date, string>> result;
	for (const auto& [date, events] : date_to_event) {
		for (const auto& event : events.order) {
			if (p(date, event)) {
				result.push_back({date, event});
			}
		}
	}
	return result;
}

int Database::RemoveIf(function<bool(const Date&, const string&)> p) {
	int removed = 0;
	queue<Date> q;

	for (auto& [date, events] : date_to_event) {
		auto& dt = date;
		auto it = stable_partition(events.order.begin(), events.order.end(),
		[&dt, &p](const string& event) {
			return !p(dt, event);
		});
		removed += events.order.end() - it;
		while (events.order.end() != it) {
			events.unique.erase(events.order[events.order.size() - 1]);
			events.order.pop_back();
		}
		if (events.order.empty()) {
			q.push(date);
		}
	}
	while (!q.empty()) {
		date_to_event.erase(q.front());
		q.pop();
	}
	return removed;
}

