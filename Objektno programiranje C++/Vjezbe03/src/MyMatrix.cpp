/*
 * MyMatrix.cpp
 *
 *  Created on: 18. ožu 2015.
 *      Author: Tomislav
 */

#include "MyMatrix.h"
MyMatrix::MyMatrix(int heigth, int length) :
		length(length), heigth(heigth) {
	checkDimension(heigth, length, false);
	data.reserve(heigth);
	std::vector<bool> insideData(length);
	for (int i = 0; i < length; ++i) {
		insideData.push_back(false);
	}
	for (int i = 0; i < heigth; ++i) {
		data.push_back(insideData);
	}
}

MyMatrix::~MyMatrix() {
}

void MyMatrix::set(int row, int column, bool value) {
	checkDimension(row, column, true);
	data[row][column] = value;
}
bool MyMatrix::get(int row, int column) const {
	checkDimension(row, column, true);
	return data[row][column];
}
int MyMatrix::getLength() const {
	return length;
}
int MyMatrix::getHeigth() const {
	return heigth;
}

void MyMatrix::checkDimension(int row, int column, bool notConstructor) const {
	if (row < 0 || column < 0) {
		throw std::invalid_argument("Negativna vrijednost parametra.");
	}
	if (notConstructor && (row >= getHeigth() || column >= getLength())) {
		throw std::invalid_argument("Overflow polja.");
	}
}
