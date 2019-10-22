//
// Created by professor on 22.10.19.
//

//
// Created by Virgil Legros on 19/10/2019.
//

#include "responses.h"
#include "bus_manager.h"
#include "query.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

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