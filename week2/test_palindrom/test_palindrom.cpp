//
// Created by professor on 21.10.19.
//
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		} catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

bool	IsPalindrom(string s)
{
	int i = 0;

	while (s[i] == s[s.size() - 1 - i] && i < s.size() / 2)
		i++;
	//if i == s.size() / 2 than two halfs of the sting are equal and the string is a palindrom
	return i == s.size() / 2;
}

void Tests() {
	Assert(IsPalindrom(""), "Empty string is a palindrom");
	Assert(IsPalindrom("h"), "One symbol string is a palindrom");
	Assert(IsPalindrom("madam"), "Wrong output");
	Assert(IsPalindrom("level"), "Wrong output");
	Assert(IsPalindrom(" wasitacaroracatisaw "), "Skipping first or last element");
	Assert(IsPalindrom("wasitacaroracatisaw"), "Wrong output");
	AssertEqual(IsPalindrom(" wasitacaroracatisaw"), false, "Skipping delimiters");
	AssertEqual(IsPalindrom("wasitacaroracatisaw "), false, "Skipping delimiters");
	AssertEqual(IsPalindrom("levdel"), false, "Wrong output");
}

int main() {
	TestRunner runner;
	runner.RunTest(Tests, "Tests for function IsPalindrom");
	// добавьте сюда свои тесты
	return 0;
}
