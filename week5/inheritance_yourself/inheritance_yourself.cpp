//
// Created by professor on 4/7/20.
//
#include <iostream>

using namespace std;

class Log {
public:
	const string log;

	Log(const string& t) : log(t) {
		cout << "+ " << log << endl;
	}
	~Log() {
		cout << "- " << log << endl;
	}
};

class Animal {
public:
	Animal(const string& t = "Animal") : Name(t),  l("Animal"){}

	const string Name;
	Log l;
};


class Dog : public Animal {
public:
	Dog(const string& t) : Animal(t), l(t) {};

	void Bark() {
		cout << Name << " barks: woof!" << endl;
	}
	Log l;
};

int main() {
	Dog dog1("Ralph");

	dog1.Bark();
	return 0;
}