//
// Created by Virgil Legros on 13/10/2019.
//

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

enum class Lang {
	DE, FR, IT
};

struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};

tuple<string,  string,  map<Lang, string>,  int64_t> CreateTupleOutOfRegion(const Region& region) {
	return tie(region.std_name, region.parent_std_name, region.names, region.population);
}

bool operator<(const Region& lhs, const Region& rhs) {
	return CreateTupleOutOfRegion(lhs) < CreateTupleOutOfRegion(rhs);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
	map<Region, int> repetitions;
	int result = 0;
	for (const auto& region : regions) {
		result = max(result, ++repetitions[region]);
	}
	return result;
}

int main() {
	cout << FindMaxRepetitionCount({
										   {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Russia",
												   "Eurasia",
												   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Russia",
												   "Eurasia",
												   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
												   89
										   },
								   }) << endl;

	cout << FindMaxRepetitionCount({
										   {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Russia",
												   "Eurasia",
												   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Moscow",
												   "Toulouse",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   31
										   },
								   }) << endl;

	return 0;
}
