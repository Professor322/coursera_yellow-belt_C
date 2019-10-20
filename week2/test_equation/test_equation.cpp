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


int GetDistinctRealRootCount(double a, double b, double c) {
	return 1;
}

///Quadratic equation
void TestNegativeDiscriminant() {
	AssertEqual(GetDistinctRealRootCount(2, 1, 2), 0, "Test Negative Discriminant");
}

void TestZeroDiscriminant() {
	AssertEqual(GetDistinctRealRootCount(1, 4, 4), 1, "Test Zero Discriminant");
}

void TestZeroBCCoefficients() {
	AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "Test Zero B and C Coefficients");
}

void TestNormalQuadraticEquation() {
	AssertEqual(GetDistinctRealRootCount(1, 3, -4), 2, "Test Normal Quadratic Equation");
}

///Linear equation
void TestZeroABCoefficients() {
	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "Test Zero A and B Coefficients");
}

void TestNormalLinearEquation() {
	AssertEqual(GetDistinctRealRootCount(0, 5, 5), 1, "Test Normal Linear Equation");
}

void	TestAll() {
	TestRunner tr;

	tr.RunTest(TestNegativeDiscriminant, "TestNegativeDiscriminant");
	tr.RunTest(TestZeroDiscriminant, "TestZeroDiscriminant");
	tr.RunTest(TestZeroBCCoefficients, "TestZeroBCCoefficients");
	tr.RunTest(TestNormalQuadraticEquation, "TestNormalQuadraticEquation");
	tr.RunTest(TestZeroABCoefficients, "TestZeroABCoefficients");
	tr.RunTest(TestNormalLinearEquation, "TestNormalLinearEquation");
}
int main() {
	TestRunner runner;
	TestAll();
	// добавьте сюда свои тесты
	return 0;
}