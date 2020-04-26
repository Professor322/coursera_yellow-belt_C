//
// Created by professor on 4/26/20.
//

#include <string>
#include <list>
#include <iostream>
#include <queue>

using namespace std;

class  Equation {
public:
	Equation(const string& num) {
		PlaceNum(num);
	}

	void AddToTheEquation(const char op, const string& num) {
		ops.push({op, num});
	}

	string GetEquation() {
		while (!ops.empty()) {
			auto new_op = ops.front();
			ops.pop();
			if (!last_added.empty()) {
				int new_op_priority = Priority(new_op.first);
				int last_added_priority = Priority(last_added.back());

				bool priority_condition = new_op_priority != last_added_priority &&
											new_op_priority > last_added_priority;

				if (priority_condition) {
					PlaceBrackets();
				}
			}
			PlaceOperator(new_op.first);
			PlaceNum(new_op.second);
			last_added.push_back(new_op.first);
		}
		return {equation.begin(), equation.end()};
	}

private:
	void PlaceNum(const string& num) {
		for (const auto& c : num) {
			equation.push_back(c);
		}
	}

	void PlaceOperator(const char op) {
		equation.push_back(' ');
		equation.push_back(op);
		equation.push_back(' ');
	}

	void PlaceBrackets() {
		equation.push_front('(');
		equation.push_back(')');
	}

	int Priority(const char op) {
		if (op == '-' || op == '+')
			return 0;
		return 1;
	}

	list<char> equation;
	queue<pair<char, string>> ops;
	list<char> last_added;
};



int 	main() {
	int n;

	cin >> n;
	Equation e(to_string(n));

	int q;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		char op;
		int num;
		cin >> op >> num;
		e.AddToTheEquation(op, to_string(num));
	}
	cout << e.GetEquation() << endl;
	return 0;
}