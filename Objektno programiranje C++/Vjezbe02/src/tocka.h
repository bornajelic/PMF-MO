/*
 * tocka.h
 *
 *  Created on: 11. 3. 2015.
 *      Author: Tomislav
 */

#ifndef tocka_H_
#define tocka_H_

#include <cmath>
#include <iostream>

class tocka {
public:
	tocka(double a = 0, double b = 0);
	virtual ~tocka();
	double distance(tocka & t2);
	double distanceSquared(tocka & t2);
	void ispisi();
	bool operator<(const tocka t2) const;
	bool operator==(const tocka &t2) const;
private:
	double A;
	double B;
	unsigned long id;
	static unsigned long idGenerator;
};

#endif /* tocka_H_ */
