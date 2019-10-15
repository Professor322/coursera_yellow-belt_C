//
// Created by professor on 15.10.19.
//

#include <map>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

template<typename T> vector<T> operator* (const vector<T>& v1, const vector<T>& v2);
template<typename First, typename Second> pair<First, Second> operator* (const pair<First, Second>& p1, const pair<First, Second>& p2);
template<typename Key, typename Value> map<Key, Value> operator* (const map<Key, Value>& m1, const map<Key, Value>& m2);


template<typename First, typename Second>
pair<First, Second> operator* (const pair<First, Second>& p1, const pair<First, Second>& p2) {
	pair<First, Second> result;

	result.first = p1.first * p2.first;
	result.second = p1.second * p2.second;
	return result;
}

template<typename T>
vector<T> operator* (const vector<T>& v1, const vector<T>& v2) {
	vector<T> result(v1.size());

	for (size_t i = 0; i < v1.size(); ++i) {
		result[i] = v1[i] * v2[i];
	}
	return result;
}

template<typename Key, typename Value>
map<Key, Value> operator* (const map<Key, Value>& m1, const map<Key, Value>& m2) {
	map<Key, Value> result;

	for (const auto& [key, value] : m1) {
		result[key] = value * m2.at(key);
	}
	return result;
}

template<typename T>
T Sqr(T value) {
	return value * value;
}
/*
int 	main() {
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
			{4, {2, 2}},
			{7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}*/