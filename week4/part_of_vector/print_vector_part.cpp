//
// Created by professor on 4/2/20.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
	auto first_negative = find_if(numbers.begin(), numbers.end(),
			[](const int& elem) {
				return elem < 0;
			});
	for (auto it = first_negative; it != numbers.begin(); ) {
		cout << *(--it) << " ";
	}
}