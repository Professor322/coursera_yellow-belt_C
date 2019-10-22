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
#include <algorithm>

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

bool	RefIsPalindrom(string s)
{
	int i = 0;

	while (s[i] == s[s.size() - 1 - i] && i < s.size() / 2)
		i++;
	//if i == s.size() / 2 than two halfs of the sting are equal and the string is a palindrom
	return i == s.size() / 2;
}

bool	IsPalindrom(string s)
{
	int i = 0;

	while (s[i] == s[s.size() - 1 - i] && i < s.size() / 2)
		i++;
	//if i == s.size() / 2 than two halfs of the sting are equal and the string is a palindrom
	return i == s.size() / 2;
}

void CourseTests() {
		Assert(IsPalindrom(""), "empty string is a palindrome");
		Assert(IsPalindrom("a"), "one letter string is a palindrome");
		Assert(IsPalindrom("abba"), "abba is a palindrome");
		Assert(IsPalindrom("abXba"), "abXba is a palindrome");
		Assert(IsPalindrom("a b X b a"), "`a b X b a` is a palindrome");
		Assert(IsPalindrom("  ABBA  "), "`  ABBA  ` is a palindrome");

		Assert(!IsPalindrom("XabbaY"), "XabbaY is not a palindrome");
		Assert(!IsPalindrom("abXYba"), "abXYba is not a palindrome");
		Assert(!IsPalindrom("Xabba"), "Xabba is not a palindrome");
		Assert(!IsPalindrom("abbaX"), "abbaX is not a palindrome");
		Assert(
				!IsPalindrom("was it a car or a cat i saw"),
				"`was it a car or a cat i saw` is not a palindrome because spaces do not match"
		);
		Assert(!IsPalindrom("ABBA   "), "`ABBA   ` is not a palindrome");
		Assert(!IsPalindrom("  ABBA"), "`  ABBA` is not a palindrome");

}

void Tests() {
	AssertEqual(IsPalindrom(""), true, "empty string");
	AssertEqual(IsPalindrom(" "), true, "whitespace");
	AssertEqual(IsPalindrom("A"), true, "A");
	AssertEqual(IsPalindrom("&"), true, "&");
	AssertEqual(IsPalindrom("1"), true, "1");
	AssertEqual(IsPalindrom("121"), true, "121");
	AssertEqual(IsPalindrom("@@"), true, "@@");
	AssertEqual(IsPalindrom("!@# #@!"), true, "!@# #@!");
	AssertEqual(IsPalindrom("madam"), true, "madam");
	AssertEqual(IsPalindrom("baobab"), false, "baobab");
	AssertEqual(IsPalindrom(" weew "), true, " weew ");
	AssertEqual(IsPalindrom("f f ff f f"), true, "f f ff f f");
	AssertEqual(IsPalindrom("f f f f f"), true, "f f f f f");
	AssertEqual(IsPalindrom("A  L L A"), false, "A  L L A");
	AssertEqual(IsPalindrom("mada m"), false, "mada m");
	AssertEqual(IsPalindrom(" weew   "), false, " weew   ");
	AssertEqual(IsPalindrom("   weew "), false, "   weew ");
	AssertEqual(IsPalindrom("qwertyTrewq"), false, "qwertyTrewq");
	AssertEqual(IsPalindrom("qwertytrewq"), true, "qwertytrewq");
	AssertEqual(IsPalindrom("qwerttrewq"), true, "qwerttrewq");
	AssertEqual(IsPalindrom("qwertytrewQ"), false, "qwertytrewQ");
	AssertEqual(IsPalindrom("Q wer ewQ"), false, "Q wer ewQ");
	AssertEqual(IsPalindrom("   qwert ytrewq   "), false, "qwert ytrewq");
	AssertEqual(IsPalindrom("7777777778"), false);
	AssertEqual(IsPalindrom("8777777777"), false);
	AssertEqual(IsPalindrom("                                           "), true);
}

int main() {
	TestRunner runner;
	runner.RunTest(Tests, "Tests for function IsPalindrom");
	// добавьте сюда свои тесты
	return 0;
}
