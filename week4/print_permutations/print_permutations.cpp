//
// Created by professor on 4/3/20.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int 	main() {

	int n;
	cin >> n;

	vector<int> nums(n);

	for (int& num :nums) {
		num = n;
		--n;
	}
/*	// iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
	// Заполняет диапазон последовательно возрастающими значениями
	iota(permutation.begin(), permutation.end(), 1);

	// reverse          -> http://ru.cppreference.com/w/cpp/algorithm/reverse
	// Меняет порядок следования элементов в диапазоне на противоположный
	reverse(permutation.begin(), permutation.end());
*/
	do {
		for (const int& num : nums) {
			cout << num << " ";
		}
		cout << endl;
	} while (prev_permutation(nums.begin(), nums.end()));

	return 0;
}