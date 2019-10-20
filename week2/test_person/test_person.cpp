//
// Created by professor on 20.10.19.
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

/*
class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		fn[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		ln[year] = last_name;
	}
	string GetFullName(int year) {
		auto it_fn = fn.lower_bound(year), it_ln = ln.lower_bound(year);
		if (it_fn == fn.end() && it_ln == ln.end()) {
			return "Incognito";
		} else if (it_fn == fn.end()) {
			return it_ln->second + " with unknown first name";
		} else if (it_ln == ln.end()){
			return it_fn->second + " with unknown last name";
		} else {
			return it_fn->second + " " + it_ln->second;
		}
	}

private:
	map<int, string, greater<int> > fn;
	map<int, string, greater<int> > ln;
};
*/

void TestIncognito() {
	Person check;

	AssertEqual(check.GetFullName(1900), "Incognito", "No values in map");
	check.ChangeFirstName(1901, "a");
	AssertEqual(check.GetFullName(1900), "Incognito", "New values should not modify previous year's values");
	check.ChangeLastName(1903, "b");
	AssertEqual(check.GetFullName(1900), "Incognito", "New values should not modify previous year's values");

}

void TestFirstNameOrLastName() {
	{
		Person check_fn;

		check_fn.ChangeFirstName(1901, "a");
		AssertEqual(check_fn.GetFullName(1901), "a with unknown last name", "Wrong output");
		check_fn.ChangeLastName(1903, "b");
		AssertEqual(check_fn.GetFullName(1902), "a with unknown last name", "Wrong output");
	}
	{
		Person check_ln;
		check_ln.ChangeLastName(1901, "a");
		AssertEqual(check_ln.GetFullName(1901), "a with unknown first name", "Wrong output");
		check_ln.ChangeFirstName(1903, "b");
		AssertEqual(check_ln.GetFullName(1902), "a with unknown first name", "Wrong output");
	}
}

void TestFullName() {
	Person check;

	check.ChangeFirstName(1901, "a");
	check.ChangeLastName(1901, "b");
	AssertEqual(check.GetFullName(1901), "a b", "Wrong output");
	check.ChangeFirstName(1905, "c");
	check.ChangeLastName(1903, "d");
	AssertEqual(check.GetFullName(1902), "a b", "Wrong output");
}

void TestChanging() {
	Person check;

	check.ChangeFirstName(1901, "a");
	check.ChangeLastName(1903, "b");
	AssertEqual(check.GetFullName(1902), "a with unknown last name", "Wrong output");
	AssertEqual(check.GetFullName(1903), "a b", "Wrong output");

	check.ChangeLastName(1905, "c");
	AssertEqual(check.GetFullName(1906), "a c", "Wrong output");

	check.ChangeFirstName(1899, "z");
	AssertEqual(check.GetFullName(1900), "z with unknown last name", "Wrong output");
	AssertEqual(check.GetFullName(1904), "a b", "Wrong output");

	check.ChangeLastName(1902, "k");
	AssertEqual(check.GetFullName(1902), "a k", "Wrong output");

}

void TestAll() {
	TestRunner tr;

	tr.RunTest(TestIncognito, "Test Incognito");
	tr.RunTest(TestFirstNameOrLastName, "Test FirstName Or LastName");
	tr.RunTest(TestFullName, "Test Full Name");
	tr.RunTest(TestChanging, "Test Changing");
}
int main() {
	TestAll();
	// добавьте сюда свои тесты
	return 0;
}