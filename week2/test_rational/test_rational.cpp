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
#include <utility>

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

template <class T, class V>
ostream& operator << (ostream& os, const pair<T, V>& s) {
	os << "{";
	os << s.first << ", " << s.second;
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
class Rational {
public:
	// Вы можете вставлять сюда различные реализации,
	// чтобы проверить, что ваши тесты пропускают корректный код
	// и ловят некорректный

	Rational();
	Rational(int numerator, int denominator) {
	}

	int Numerator() const {
	}

	int Denominator() const {
	}
};
*/
void TestDefault() {
	Rational fraction;

	AssertEqual(make_pair(fraction.Numerator(), fraction.Denominator()), make_pair(0, 1), "Constructor Error");
}

void TestFractionReduction() {
	{
		Rational fraction(4, 6);

		AssertEqual(make_pair(fraction.Numerator(), fraction.Denominator()), make_pair(2, 3), "Wrong reduction");
	}
	{
		Rational fraction(150, 200);
		AssertEqual(make_pair(fraction.Numerator(), fraction.Denominator()), make_pair(3, 4), "Wrong reduction");
	}
}

void TestNegativeFraction() {
	{
		Rational fraction(-7, 8);

		AssertEqual(make_pair(fraction.Numerator(), fraction.Denominator()), make_pair(-7, 8));
	}
	{
		Rational fraction(3,-4);

		AssertEqual(make_pair(fraction.Numerator(), fraction.Denominator()), make_pair(-3, 4));
	}
	{
		Rational fraction(-7, -8);

		AssertEqual(make_pair(fraction.Numerator(), fraction.Denominator()), make_pair(7, 8));
	}

}

void TestZeroNumerator() {
	Rational fraction(0, 10);

	AssertEqual(make_pair(fraction.Numerator(), fraction.Denominator()), make_pair(0, 1));

}

int main() {
	TestRunner runner;
	runner.RunTest(TestDefault, "Test default constructor");
	runner.RunTest(TestFractionReduction, "Test Fraction Reduction");
	runner.RunTest(TestNegativeFraction, "Test Negative Fraction");
	runner.RunTest(TestZeroNumerator, "Test Zero Numerator");
	// добавьте сюда свои тесты
	return 0;
}