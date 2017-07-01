/*
 * GameOL.cpp
 *
 *  Created on: 18. ožu 2015.
 *      Author: Tomislav
 */

#include "GameOL.h"

const char GameOL::NO_CELL = ' ', GameOL::ALIVE_CELL = '*', GameOL::END_OF_ROW =
		'\n';

GameOL::GameOL() {
	notInitialised = true;
	nextMatrix = NULL;
	currentMatrix = NULL;
}

GameOL::~GameOL() {
	delete (currentMatrix);
	delete (nextMatrix);
}

bool isNumber(std::string & s) {
	for (char c : s) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

void GameOL::init(std::string const & file_name) {
	std::ifstream file;
	file.open(file_name.c_str());

	int br = 0, *dim = new int[2]();
	std::string buff;

	while ((2 > br) && (file >> buff)) {
		if (isNumber(buff)) {
			dim[br] = std::atoi(buff.c_str());		//ne prepoznaje mi std:stoi
		}
		++br;
	}

	if (br < 2 || dim[0] < 1 || dim[1] < 1) {
		delete dim;
		file.close();
		throw std::domain_error("Pogrešno strukturiran inputni file.");
	}

	currentMatrix = new MyMatrix(dim[0], dim[1]);
	nextMatrix = new MyMatrix(dim[0], dim[1]);

	std::string buffer;
	br = 0;
	/*std::getline(file, buffer);
	 std::cout << 1 << ". \"" << buffer  << "\"" << std::endl;
	 std::getline(file, buffer);
	 std::cout << 2 << ". \"" << buffer  << "\"" << std::endl;
	 std::getline(file, buffer);
	 std::cout <<3 << ". \"" << buffer  << "\"" << std::endl;*/

	std::getline(file, buffer); //preskace kraj prve linije
	while (std::getline(file, buffer) && (br < dim[0])) {
		/*if (br++ >= dim[0]) {
		 break;
		 }
		 std::cout << br << ". \"" << buffer  << "\"" << std::endl;
		 */
		//std::cout << br << ". \"" << buffer.length()  << "\"" << std::endl;
		for (int i = 0, max = std::min((int) buffer.length(), dim[1]); i < max;
				++i) {
			if (buffer[i] == ALIVE_CELL) {
				currentMatrix->set(br, i, true);
			} else if (buffer[i] != NO_CELL && buffer[i] != 0) {
				throw std::domain_error("Pogrešno strukturiran inputni file.");
			}
		}
		br++;
	}

	notInitialised = false;

	delete dim;
	file.close();
}

void GameOL::print(std::ostream & outputStream) const {
	if (notInitialised) {
		return;
	}

	int curr_i = 0, curr_j = 0;

	char toPrint;
	int br = 0;
	while (curr_i < currentMatrix->getHeigth() - 1
			|| (curr_i == currentMatrix->getHeigth() - 1
					&& curr_j <= currentMatrix->getLength())) {
		if (curr_j == currentMatrix->getLength()) {
			curr_j = 0;
			curr_i++;
			toPrint = END_OF_ROW;
		} else {
			toPrint =
					currentMatrix->get(curr_i, curr_j++) ? ALIVE_CELL : NO_CELL;
		}
		++br;
		outputStream << toPrint;
	}

}

void GameOL::print() const {
	print(std::cout);
}
void GameOL::print(std::string const & file_name) const {
	if (notInitialised) {
		return;
	}
	std::ofstream file;
	file.open(file_name);
	file << currentMatrix->getHeigth() << " " << currentMatrix->getLength() << "\n";
	print(file);
	file.close();
}
void GameOL::update() {
	if (notInitialised) {
		return;
	}
	auto calculatePositionValue =
			[&](int row, int column) -> bool {
				int neighbour = br_susjeda(row, column);
				if ((currentMatrix->get(row, column) && neighbour == 2) || neighbour == 3) {
					return true;
				}
				return false;
			};
	for (int row = 0; row < currentMatrix->getHeigth(); ++row) {
		for (int column = 0; column < currentMatrix->getLength(); ++column) {
			nextMatrix->set(row, column, calculatePositionValue(row, column));
		}
	}
	MyMatrix *tmp = currentMatrix;
	currentMatrix = nextMatrix;
	nextMatrix = tmp;
}

int GameOL::br_susjeda(int i, int j) const {
	int neighbours = 0;
	for (int row = i - 1; row <= i + 1; ++row) {
		for (int column = j - 1; column <= j + 1; ++column) {
			if (row < 0 || column < 0 || (row == i && column == j)
					|| row >= currentMatrix->getHeigth()
					|| column >= currentMatrix->getLength()) {
				continue;
			}
			neighbours += currentMatrix->get(row, column);
		}
	}
	return neighbours;
}
