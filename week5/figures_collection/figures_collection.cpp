//
// Created by professor on 4/7/20.
//
#include <vector>
#include <sstream>
#include <iostream>
#include <memory>
#include <cmath>
#include <iomanip>

using namespace std;

class Figure {
public:
	Figure(const string& name = "figure") :
	 _name(name) {}

	virtual string Name() const = 0;
	virtual double Area() const = 0;
	virtual double Perimeter() const = 0;

protected:
	const string _name;
	double _perimeter;
	double _area;
};


class Rect : public Figure {
public:
	Rect(const int width, const int height) : Figure("RECT") {
		_perimeter = (width + height) * 2.0;
		_area = width * height;
	}

	string Name() const override {
		return _name;
	}

	double Area() const override  {
		return _area;
	}

	double Perimeter() const override  {
		return _perimeter;
	}
};



class Triangle : public Figure {
public:
	Triangle(const int a, const int b, const int c) : Figure("TRIANLGE") {
		_perimeter = a + b + c;
		_area = sqrtl((_perimeter / 2.0) * (_perimeter / 2.0 - a) *
				(_perimeter / 2.0 - b) * (_perimeter / 2.0 - c));
	}

	string Name() const override {
		return _name;
	}

	double Area() const override  {
		return _area;
	}

	double Perimeter() const override  {
		return _perimeter;
	}
};

class Circle : public Figure {
public:
	Circle(const int& radius) : Figure("CIRCLE") {
		_perimeter = 2.0 * PI * radius;
		_area = PI * pow(radius, 2.0);
	}

	string Name() const override {
		return _name;
	}

	double Area() const override  {
		return _area;
	}

	double Perimeter() const override  {
		return _perimeter;
	}

private:
	const double PI = 3.14;
};



shared_ptr<Figure> CreateFigure(istringstream& is) {
	string figure_type;

	is >> figure_type;
	if (figure_type == "RECT") {
		int width, height;

		is >> width >> height;
		return make_shared<Rect>(width, height);

	} else if (figure_type == "CIRCLE") {
		int radius;

		is >> radius;
		return make_shared<Circle>(radius);

	} else if (figure_type == "TRIANGLE") {
		int a, b, c;

		is >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	}
}


int main() {


	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		} else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					 << current_figure->Name() << " "
					 << current_figure->Perimeter() << " "
					 << current_figure->Area() << endl;
			}
		}
	}
	return 0;
}