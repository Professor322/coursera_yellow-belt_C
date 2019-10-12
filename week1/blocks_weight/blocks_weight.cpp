//
// Created by professor on 13.10.19.
//

#include <iostream>

using namespace std;

int 	main() {
	int16_t r;
	int 	n;
	u_int64_t mass_summary = 0;

	cin >> n >> r;
	for (int i = 0; i < n; ++i) {
		int w, h, d;

		cin >> w >> h >> d;
		mass_summary +=  static_cast<uint64_t>(w) * h * d * r;

	}
	cout << mass_summary << endl;
	return 0;
}