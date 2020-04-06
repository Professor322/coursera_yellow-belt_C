//
// Created by professor on 4/6/20.
//
#include <set>
#include <iostream>

using namespace std;

set<int>::const_iterator FindNearestElement(
		const set<int>& numbers,
		int border) {

	if (numbers.empty()) {
		return numbers.end();
	}

	auto equal_or_greater = numbers.lower_bound(border);
	auto less  = numbers.end();

	if (equal_or_greater != numbers.begin()) {
		less = prev(equal_or_greater);
	}

	if (less != numbers.end()) {
		if (abs(*equal_or_greater - border) < abs(*less - border))
			return equal_or_greater;
		
		return less;
	}
	return equal_or_greater;
}

/*
int main() {
	set<int> numbers = {1, 4, 6};
	cout <<
		 *FindNearestElement(numbers, 0) << " " <<
		 *FindNearestElement(numbers, 3) << " " <<
		 *FindNearestElement(numbers, 5) << " " <<
		 *FindNearestElement(numbers, 6) << " " <<
		 *FindNearestElement(numbers, 100) << endl;

	set<int> empty_set;

	cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
	return 0;
}*/