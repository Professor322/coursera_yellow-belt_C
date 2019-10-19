//
// Created by Virgil Legros on 19/10/2019.
//

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;
using StrToVec = map<string, vector<string> >;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	string option;

	is >> option;
	if (option == "NEW_BUS") {
		int stop_count;

		q.type = QueryType::NewBus;
		is >> q.bus >> stop_count;
		q.stops.resize(stop_count);
		for (auto& stop : q.stops) {
			is >> stop;
		}
	} else if (option == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	} else if (option == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	} else if (option == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
	return is;
}

struct BusesForStopResponse {
	vector<string> buses_to_stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.buses_to_stop.empty()) {
		return os << "No stop";
	}
	for(const auto& bus : r.buses_to_stop) {
		os << bus << " ";
	}
	return os;
}

struct StopsForBusResponse {
	string bus;
	vector<string> stops_to_bus;
	StrToVec buses_to_stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {

	if (r.stops_to_bus.empty()) {
		return os << "No bus";
	}
	size_t i = 0;
	for (const auto& stop : r.stops_to_bus) {
		os << "Stop " << stop << ": ";
		if (r.buses_to_stops.at(stop).size() == 1) {
			os << "no interchange";
		} else {
			for (const auto& other_bus : r.buses_to_stops.at(stop)) {
				if (r.bus != other_bus) {
					os << other_bus << " ";
				}
			}
		}
		if (i++ + 1 != r.stops_to_bus.size()) {
			os << endl;
		}
	}
	return os;
}

struct AllBusesResponse {
	StrToVec buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {

	if (r.buses_to_stops.empty()) {
		return os << "No buses";
	}
	size_t i = 0;
	for (const auto& [bus, stops] : r.buses_to_stops) {
		os << "Bus " << bus << ": ";
		for (const auto& stop : stops) {
			os << stop << " ";
		}
		if (i++ + 1 != r.buses_to_stops.size()) {
			os << endl;
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		this->buses_to_stops[bus] = stops;
		for (const auto& stop : this->buses_to_stops[bus]) {
			this->stops_to_buses[stop].push_back(bus);
		}
	}
	BusesForStopResponse GetBusesForStop(const string& stop) const {
		if (this->stops_to_buses.count(stop)) {
			return {this->stops_to_buses.at(stop)};
		}
		return {{}};
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		if (this->buses_to_stops.count(bus)) {
			return {bus, this->buses_to_stops.at(bus), this->stops_to_buses};
		}
		return {"Doesn't exist", {}, this->stops_to_buses};
	}

	AllBusesResponse GetAllBuses() const {
		if (!this->buses_to_stops.empty())
			return {this->buses_to_stops};
		return {{}};
	}
private:
	StrToVec buses_to_stops;
	StrToVec stops_to_buses;
};


int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
			case QueryType::NewBus:
				bm.AddBus(q.bus, q.stops);
				break;
			case QueryType::BusesForStop:
				cout << bm.GetBusesForStop(q.stop) << endl;
				break;
			case QueryType::StopsForBus:
				cout << bm.GetStopsForBus(q.bus) << endl;
				break;
			case QueryType::AllBuses:
				cout << bm.GetAllBuses() << endl;
				break;
		}
	}
	return 0;
}