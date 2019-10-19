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

};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {

	return os;
}

struct StopsForBusResponse {

};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {

	return os;
}

struct AllBusesResponse {

};

ostream& operator << (ostream& os, const AllBusesResponse& r) {

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

	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {

	}

	AllBusesResponse GetAllBuses() const {

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