/*
 * Matrix.h
 *
 *  Created on: 8. tra 2015.
 *      Author: Tomislav
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <array>
#include <initializer_list>
#include <utility>

// Matrica sa statièki zadanim dimenzijama. Nije moguæa realokacija.
// rows = broj redaka, cols = broj stupaca
template<int rows, int cols>
class Matrix {
public:
	static double EPSILON;
	Matrix(const std::initializer_list<std::initializer_list<double> > & list);

	explicit Matrix(double d) :
			mData() {
		mData.fill(d);
	}

	Matrix() :
			mData() {

	}

	Matrix(const Matrix &);
	Matrix(Matrix &&);

	// operatori indeksiranja: i=redak, j=stupac
	double & operator()(unsigned int i, unsigned int j) {
		return mData[i * cols + j];
	}

	double const & operator()(unsigned int i, unsigned int j) const {
		return mData[i * cols + j];
	}

	// postavi sve elemente na nulu
	void zero();
	// postavi na jediniènu matricu
	void eye();

	Matrix<rows, cols>& operator+=(const Matrix &);
	Matrix<rows, cols>& operator-=(const Matrix &);
	explicit operator bool() const;

	Matrix<rows, cols>& operator=(const Matrix &);

	Matrix<rows, cols>& operator=(Matrix &&);
private:
	// Pamtimo elemente zapisane po recima
	std::array<double, rows * cols> mData;
};

template<int rows, int cols>
double Matrix<rows, cols>::EPSILON = 2e-10;

template<int rows, int cols>
std::ostream& operator<<(std::ostream & out,
		const Matrix<rows, cols> & matrix) {
	out << "[\n";
	for (int i = 0; i < rows; ++i) {
		out << "\t[";
		for (int j = 0; j < cols; ++j) {
			if (j != 0) {
				out << ", ";
			}
			out << matrix(i, j);
		}
		out << "]\n";
	}
	out << " ]";
	return out;
}

template<int m, int n, int k>
Matrix<m, k> operator*(const Matrix<m, n> & m1, const Matrix<n, k> & m2) {
	Matrix<m, k> result;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < k; ++j) {
			for (int t = 0; t < n; ++t) {
				result(i, j) += (m1(i, t) * m2(t, j));
			}
		}
	}
	return result;
}

template<int rows, int cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator=(Matrix && m) {
	if (&m != this) {
		mData = std::move(m.mData);
	}
	return *this;
}

template<int rows, int cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator=(const Matrix &m) {
	if (&m != this) {
		mData = m.mData;
	}
	return *this;
}

template<int rows, int cols>
Matrix<rows, cols>::Matrix(const Matrix & m) :
		mData(m.mData) {
}

template<int rows, int cols>
Matrix<rows, cols>::Matrix(Matrix && m) :
		mData(std::move(m.mData)) {
}

template<int rows, int cols>
Matrix<rows, cols>::Matrix(
		const std::initializer_list<std::initializer_list<double> > & list) :
		mData() {
	int br = 0;
	for (const auto & i : list) {
		for (const auto & j : i) {
			mData[br++] = j;
		}
	}
}

template<int rows, int cols>
Matrix<rows, cols> operator+(const Matrix<rows, cols> matrix1,
		const Matrix<rows, cols> & matrix2) {
	return Matrix<rows, cols>(matrix1) += matrix2;
}

template<int rows, int cols>
Matrix<rows, cols> operator-(const Matrix<rows, cols> matrix1,
		const Matrix<rows, cols> & matrix2) {
	return Matrix<rows, cols>(matrix1) -= matrix2;
}

template<int rows, int cols>
Matrix<rows, cols> operator*(const Matrix<rows, cols> matrix, double scalar) {
	Matrix<rows, cols> result(matrix);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			result(i, j) *= scalar;
		}
	}
	return result;
}

template<int rows, int cols>
Matrix<rows, cols> operator*(double scalar, const Matrix<rows, cols> & m) {
	return m * scalar;
}

template<int rows, int cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator+=(const Matrix & m) {
	for (int index = 0, max = rows * cols; index < max; ++index) {
		mData[index] += m.mData[index];
	}
	return *this;
}

template<int rows, int cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator-=(const Matrix & m) {
	for (int index = 0, max = rows * cols; index < max; ++index) {
		mData[index] -= m.mData[index];
	}
	return *this;
}

template<int rows, int cols>
Matrix<rows, cols>::operator bool() const {
	double EPSILON_NEG = -EPSILON;
	for (double d : mData) {
		if (d > EPSILON || d < EPSILON_NEG) {
			return false;
		}
	}
	return true;
}

template<int rows, int cols>
void Matrix<rows, cols>::zero() {
	for (int index = 0, max = rows * cols; index < max; ++index) {
		mData[index] = 0;
	}
}

template<int rows, int cols>
void Matrix<rows, cols>::eye() {
	for (int index = 0, max = rows < cols ? rows : cols; index < max; ++index) {
		operator()(index, index) = 1;
	}
}

#endif /* MATRIX_H_ */
