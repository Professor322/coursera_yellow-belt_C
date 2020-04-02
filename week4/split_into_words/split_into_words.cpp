//
// Created by professor on 4/2/20.
//

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
	stringstream ss(s);

	vector<string> words;
	string::const_iterator begin_it, end_it = s.begin();

	do  {

		begin_it = *end_it == ' ' ? end_it + 1 : end_it;
		end_it = find(begin_it, s.end(), ' ');
		words.push_back({begin_it, end_it});

	} while (end_it != s.end());

	return words;
}
/*
int main() {
	string s = "C Cpp Java Python";

	vector<string> words = SplitIntoWords(s);
	cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			cout << "/";
		}
		cout << *it;
	}
	cout << endl;

	return 0;
}*/