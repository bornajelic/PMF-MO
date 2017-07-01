/*
 * tocka.cpp
 *
 *  Created on: 11. 3. 2015.
 *      Author: Tomislav
 */

#include "tocka.h"

unsigned long tocka::idGenerator = 0;

tocka::tocka(double a, double b) :
		A(a), B(b) {
	id = idGenerator++;
}

double tocka::distance(tocka & t2) {
	return std::sqrt(distanceSquared(t2));
}

double tocka::distanceSquared(tocka & t2) {
	return (A - t2.A)*(A - t2.A) + (B - t2.B)*(B - t2.B);
}

void tocka::ispisi() {
	std::cout << "(" << A << "," << B << ")";
}

bool tocka::operator<(const tocka t2) const {
	return id < t2.id;
	/*if (A < t2.A) {
		return true;
	} else if (A == t2.A && B < t2.B) {
		return true;
	}
	return false;*/
}

bool tocka::operator==(const tocka &t2) const {
	return id == t2.id;
}

tocka::~tocka() {
}
