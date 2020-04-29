//
// Created by professor on 4/26/20.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
	Human(const string& name, const string& Position)
	: Name(name),
	Position(Position) {}

	virtual void Walk(const string& destination) const = 0;
public:
	const string Name;
	const string Position;
};

class Student : public Human {
public:

	Student(const string& name, const string& favouriteSong) :
	Human(name, "Student"),
	FavouriteSong(favouriteSong) {}

	void Learn() {
		cout << Position << ": " << Name << " learns" << endl;
	}

	void Walk(const string& destination) const override {
		cout << Position << ": " << Name << " walks to: " << destination << endl;
		cout << Position << ": " << Name << " sings a song: " << FavouriteSong << endl;
	}

	void SingSong() {
		cout << Position << ": "<< Name << " sings a song: " << FavouriteSong << endl;
	}

private:
	const string FavouriteSong;
};


class Teacher : public Human {
public:

	Teacher(const string& name, const string& subject) :
	Human(name, "Teacher"),
	Subject(subject) {}


	void Teach() {
		cout << Position << ": " << Name << " teaches: " << Subject << endl;
	}

	void Walk(const string& destination) const override {
		cout << Position << ": " << Name << " walks to: " << destination << endl;
	}

private:
	const string Subject;
};


class Policeman : public Human {
public:
	Policeman(const string& name) : Human(name, "Policeman") {}

	void Check(const Human& human) {
		cout << Position << ": " << Name <<
		" checks "<< human.Position <<
		     ". " << human.Position <<
		     "'s name is: " << human.Name<< endl;
	}

	void Walk(const string& destination) const override {
		cout << Position << ": " << Name << " walks to: " << destination << endl;
	}
};


void VisitPlaces(const Human& t, const vector<string>& places) {
	for (const auto& p : places) {
		t.Walk(p);
	}
}



int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, {"Moscow", "London"});
	p.Check(s);
	VisitPlaces(s, {"Moscow", "London"});
	return 0;
}
