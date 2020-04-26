//
// Created by professor on 4/25/20.
//
#include <string>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename RandomIt>
RandomIt UpperBound(RandomIt range_begin, RandomIt range_end,
						const string& prefix) {
	auto left = range_begin - 1, right = range_end;

	while (left + 1 < right) {
		auto mid = left + (right - left) / 2;
		if (prefix < (*mid).substr(0, prefix.size())) {
			right = mid;
		} else {
			left = mid;
		}
	}
	return right;
}

template <typename RandomIt>
RandomIt LowerBound(RandomIt range_begin, RandomIt range_end,
					  const string& prefix) {
	auto left = range_begin - 1, right = range_end;

	while (left + 1 < right) {
		auto mid = left + (right - left) / 2;
		if (prefix <= (*mid).substr(0, prefix.size())) {
			right = mid;
		} else {
			left = mid;
		}
	}
	return right;
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
		RandomIt range_begin, RandomIt range_end,
		const string& prefix) {
	return {
		LowerBound(range_begin, range_end, prefix),
		UpperBound(range_begin, range_end, prefix)
	};
}

int main() {
	const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

	const auto mo_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
	for (auto it = mo_result.first; it != mo_result.second; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	const auto mt_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
	cout << (mt_result.first - begin(sorted_strings)) << " " <<
		 (mt_result.second - begin(sorted_strings)) << endl;

	const auto na_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
	cout << (na_result.first - begin(sorted_strings)) << " " <<
		 (na_result.second - begin(sorted_strings)) << endl;

	return 0;
}

