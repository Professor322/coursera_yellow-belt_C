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

	int part = copy_range.size() / 3;

	auto partition_point1 = copy_range.begin() + part;
	auto partition_point2 = copy_range.begin() + part * 2;

	MergeSort(copy_range.begin(), partition_point1);
	MergeSort(partition_point1, partition_point2);
	MergeSort(partition_point2, copy_range.end());

	vector<typename RandomIt::value_type> temp_range;

	merge(copy_range.begin(), partition_point1,
		  partition_point1, partition_point2,
		  back_inserter(temp_range));

	merge(temp_range.begin(), temp_range.end(),
			partition_point2, copy_range.end(),
			range_begin);
}
/*
int main() {
	vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}
*/