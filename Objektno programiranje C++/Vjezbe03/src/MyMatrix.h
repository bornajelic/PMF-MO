/*
 * MyMatrix.h
 *
 *  Created on: 18. ožu 2015.
 *      Author: Tomislav
 */

#ifndef SRC_MYMATRIX_H_
#define SRC_MYMATRIX_H_

#include <stdexcept>
#include <vector>

class MyMatrix {
public:
	MyMatrix(int heigth = 0, int length = 0);
	~MyMatrix();
	void set(int row, int column, bool data);
	bool get(int row, int column) const;
	int getLength() const;
	int getHeigth() const;
	//void print();
private:
	int length, heigth;
	void checkDimension(int row, int column, bool notConstructor) const;
	std::vector<std::vector<bool> > data;
};
#endif /* SRC_MYMATRIX_H_ */
