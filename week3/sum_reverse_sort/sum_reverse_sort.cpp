//
// Created by professor on 22.10.19.
//

#include "sum_reverse_sort.h"
#include <algorithm>

int Sum(int x, int y) {
	return x + y;
}
string Reverse(string s) {
	reverse(s.begin(), s.end());
	return s;
}
void Sort(vector<int>& nums) {
	sort(nums.begin(), nums.end());
}
/*
int main() {
	vector<int> nums = {5, 7, 4};
	string s = "SOSI XIY";

	cout << nums[0] << nums[1] << nums[2] << endl;
	cout << Sum(5,6) << endl;
	cout << Reverse(s) << endl;
	Sort(nums);
	cout << nums[0] << nums[1] << nums[2] << endl;
	return 0;
}*/