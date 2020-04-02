//
// Created by professor on 4/2/20.
//
#include <vector>
#include <set>
#include <iostream>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
	auto it = elements.upper_bound(border);
	return {it, elements.end()};
}
