/*
 * GameOL.h
 *
 *  Created on: 18. ožu 2015.
 *      Author: Tomislav
 */

#ifndef SRC_GAMEOL_H_
#define SRC_GAMEOL_H_

#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include "MyMatrix.h"

class GameOL {
public:
	GameOL();
	virtual ~GameOL();
	void init(std::string const & file_name);
	void print() const;
	void print(std::string const & file_name) const;
	void update();
private:
	// broj živih susjeda danog elementa (i,j)
	int br_susjeda(int i, int j) const;
	MyMatrix *currentMatrix, *nextMatrix;
	bool notInitialised;
	static const char NO_CELL, ALIVE_CELL, END_OF_ROW;
	void print(std::ostream & outputStream) const;
};

#endif /* SRC_GAMEOL_H_ */
