//
// Created by professor on 13.10.19.
//

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int		main() {
	int n;
	int64_t sum = 0;

	cin >> n;

	vector<int> temperature(n);
	for (auto& item : temperature) {
		cin >> item;
		sum += item;
	}
	int64_t	avg = sum / n;
	cout << count_if(temperature.begin(),
			temperature.end(),
			[avg](int elem){return elem > avg;}) << endl;
	for (size_t i = 0; i < temperature.size(); ++i) {
		if (temperature[i] > avg) {
			cout << i << " ";
		}
	}
	return 0;
}