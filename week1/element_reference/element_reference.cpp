//
// Created by professor on 15.10.19.
//

#include <map>
#include <string>
#include <iostream>
#include <exception>

using namespace std;

template<typename K, typename V>
V& GetRefStrict(map<K, V>& m, K key) {
	try {
		return m.at(key);
	} catch(const out_of_range&) {
		throw runtime_error("Run Time Error");
	}
}
/*
int 	main() {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 3);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
	return 0;
}*/