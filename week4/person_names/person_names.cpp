//
// Created by professor on 4/6/20.
//

#include <string>
#include <map>
#include <iostream>

using namespace std;



class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		first_names.insert({year, first_name});
	}
	void ChangeLastName(int year, const string& last_name) {
		last_names.insert({year, last_name});
	}
	string GetFullName(int year) {
		auto first_name = check_changing(first_names, year);
		auto last_name = check_changing(last_names, year);

		if (first_name != first_names.end() && last_name != last_names.end()) {
			return first_name->second + " " + last_name->second;
		}

		if (first_name != first_names.end() || last_name != last_names.end()) {
			if (first_name != first_names.end()) {
				return first_name->second + " with unknown last name";
			}
			return last_name->second + " with unknown first name";
		}

		return "Incognito";
	}
private:

	map<int, string>::const_iterator
	check_changing(const map<int, string>& names, const int year) {
		if (names.empty()) {
			return names.end();
		}

		auto name = names.lower_bound(year);
		if (name->first == year) {
			return name;
		}
		if (name != names.begin()) {
			return prev(name);
		}
		return names.end();
	}

	map<int, string> first_names;
	map<int, string> last_names;
};
/*
int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	return 0;
}*/