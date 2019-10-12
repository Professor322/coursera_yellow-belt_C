//
// Created by professor on 11.10.19.
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix{
public:
	Matrix() {
		this->num_rows = 0;
		this->num_cols = 0;
	};
	Matrix(int num_rows, int num_cols);
	void Reset(int new_num_rows, int new_num_cols) {

		if (new_num_rows < 0 || new_num_cols < 0) {
			throw out_of_range("Error");
		}
		if (!new_num_rows || !new_num_cols) {
			new_num_rows = new_num_cols = 0;
		}
		this->num_rows = new_num_rows;
		this->num_cols = new_num_cols;
		matrix.resize(num_rows);
		for (auto& rows : matrix) {
			rows.assign(num_cols, 0);
		}

	}
	int At(int i, int j) const {
		if (i >= num_rows || j >= num_cols || i < 0 || j < 0) {
			throw out_of_range("Error");
		}
		return matrix[i][j];
	}
	int& At(int i, int j) {
		if (i >= num_rows || j >= num_cols || i < 0 || j < 0) {
			throw out_of_range("Error");
		}
		return matrix[i][j];
	}
	int GetNumRows() const {
		return num_rows;
	}
	int GetNumColumns() const {
		return num_cols;
	}
private:
	vector<vector<int> > matrix;
	int num_rows;
	int num_cols;
};

Matrix::Matrix(int new_num_rows, int new_num_cols){
	Reset(new_num_rows, new_num_cols);
}

istream& operator>>(istream& stream, Matrix& matrix) {

	int num_rows = 0, num_cols = 0;

	stream >> num_rows >> num_cols;
	matrix = Matrix(num_rows, num_cols);
	if (num_rows && num_cols) {
		for (int i = 0; i < num_rows; ++i) {
			for (int j = 0; j < num_cols; ++j) {
				int &elem = matrix.At(i, j);
				stream >> elem;
			}
		}
	}
	return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	bool condition = lhs.GetNumColumns() == rhs.GetNumColumns();
	condition = condition && lhs.GetNumRows() == rhs.GetNumRows();

	if (condition) {
		for (int i = 0; i < lhs.GetNumRows(); ++i) {
			for (int j = 0; j < lhs.GetNumColumns(); ++j) {
				if (lhs.At(i, j) != rhs.At(i, j)) {
					return false;
				}
			}
		}
		return true;
	}

	return (false);
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {

	stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
	for (int i = 0; i < matrix.GetNumRows(); ++i) {
		for (auto j = 0; j < matrix.GetNumColumns(); ++j) {
			stream << matrix.At(i , j);
			if (j != matrix.GetNumColumns() - 1)
				stream << " ";
		}
		if (i != matrix.GetNumRows() - 1) {
			stream << endl;
		}
	}
	return stream;
}

Matrix	operator+(const Matrix& lhs, const Matrix& rhs) {
	bool condition = lhs.GetNumColumns() == rhs.GetNumColumns();

	condition = condition && lhs.GetNumRows() == rhs.GetNumRows();
	if (!condition) {
		throw invalid_argument("Error");
	}
	Matrix new_matrix(lhs.GetNumRows(), lhs.GetNumColumns());
	for (int i = 0; i < lhs.GetNumRows(); ++i) {
		for (int j = 0; j < lhs.GetNumColumns(); ++j) {
			int& elem = new_matrix.At(i, j);
			elem = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return new_matrix;
}


int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << (one == two) << endl;
	return 0;
}