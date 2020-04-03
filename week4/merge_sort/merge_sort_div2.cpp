//
// Created by professor on 4/4/20.
//

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin < 2) {
		return ;
	}
	vector<typename RandomIt::value_type> copy_range(range_begin, range_end);

	auto partition_point = copy_range.begin() + copy_range.size() / 2;
	MergeSort(copy_range.begin(), partition_point);
	MergeSort(partition_point, copy_range.end());

	merge(copy_range.begin(), partition_point,
			partition_point, copy_range.end(),
			range_begin);
}
/*
int main() {
	vector<int> v = {8, 6 , 4,  7,  6, 4, 4, 0, 1};
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}*/