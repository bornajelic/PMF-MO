#include "surd.h"
#include <iostream>
using namespace std;

static double LAMBDA = 0.001;

Surd::Surd() {
	x = 0;
	y = 0;
	r = 0;
	NS = false;
};

Surd::Surd(int x_) {
	x = x_;
	y = 0;
	r = 0;
	NS = false;
};

Surd::Surd(int x_, int y_, int r_) {
	x = x_;
	y = y_;
	r = r_;
	NS = false;
	
	int c = abs(r), counter = 2;
	while ((double)counter < sqrt((double) c) + 1) {
		bool notChanged = true;
		if (c % (counter*counter) == 0) {
			notChanged = false;
			c /= (counter*counter);
			y *= counter;
		}
		if (notChanged) {
			if (counter > 2) {
				counter += 2;
			} else {
				counter++;
			}
		}
	}
	//vraca predznak od r:
	r = r < 0 ? -c : c;
	//rjesava se korijena ako je moguce:
	if (r == 1) {
		x = x + y;
		y = 0;
		r = 0;
	}
};

Surd::Surd(bool ns) {
	x = 0;
	y = 0;
	r = 0;
	NS = ns;
}

Surd Surd::NaS = Surd(true);

Surd evaluate(const Surd surd) {
	if (surd.NS) {
		Surd s(0, 0, 0);
		s.NS = true;
		return s;
	}
	if (surd.y == 0 || surd.r == 0) {
		return Surd(surd.x, 0, 0);
	}
	
	int a = surd.x, b = surd.y, c = abs(surd.r), counter = 2;
	while ((double)counter < sqrt((double) c) + 1) {
		bool notChanged = true;
		if (c % (counter*counter) == 0) {
			notChanged = false;
			c /= (counter*counter);
			b *= counter;
		}
		if (notChanged) {
			if (counter > 2) {
				counter += 2;
			} else {
				counter++;
			}
		}
	}
	//vraca predznak od r:
	c = surd.r < 0 ? -c : c;
	//rjesava se korijena ako je moguce:
	if (c == 1) {
		a = a + b;
		b = 0;
		c = 0;
	}
	return Surd(a, b, c);
};

Surd::operator double()const{
	if (NS || r < 0) {
		return 0;
	}
	return (double)x + ((double)y)*sqrt((double)r);
};

ostream& operator<<(ostream& f, const Surd currentSurd) {
	if (currentSurd.NS) {
		return f << "NaS";
	}
	Surd surd = evaluate(currentSurd);
	if (0 == surd.x == surd.y == surd.r) {
		return f << 0;
	}
	//x:
	if (surd.x != 0) {
		f << surd.x;
		if (surd.y == 0 || surd.r == 0) {
			return f;
		}
		if (surd.y > 0) {
			f << "+";
		}
	}
	// y:
	if (abs(surd.y) == 1) {
		f << ((surd.y < 0) ?  "-" : "");
		f << ((surd.r == 1) ? "1" : "");
	} else {
		f << surd.y;
	}
	// i:
	if (surd.r < 0) {
		f << "i";
	}
	// r:
	if (abs(surd.r) != 1) {
		f << "@" << abs(surd.r);
	}
	
	return f;
};

int& Surd::operator++() {
	return x;
};

int& Surd::operator++( int ) {

	return y;
};

int const& Surd::operator++() const {
	return x;
};

int const& Surd::operator++( int ) const {
	return y;
};

bool operator==(const Surd &s1, const Surd &s2) {
	if (s1.NS || s2.NS) {
		return false;
	}
	double sd1 = (double)s1, sd2 = (double)s2;
	return (sd1 - sd2 < LAMBDA && sd1 - sd2 > -LAMBDA);
};

bool operator<(const Surd &s1, const Surd &s2) {
	if (s1.NS || s2.NS || s1.r < 0 || s2.r < 0) {
		return false;
	}
	return ((double)s1 < (double)s2);
};

Surd operator+(const Surd &s1, const Surd &s2) {
	if (s1.NS || s2.NS) {
		Surd s(0, 0, 0);
		s.NS = true;
		return s;
	}
	Surd surd1 = evaluate(s1), surd2 = evaluate(s2);
	if (surd1.r != surd2.r && surd1.y != 0 && surd2.y!=0) {
		Surd s(0, 0, 0);
		s.NS = true;
		return s;
	}
	if (surd1.r == 0) {
		return Surd(surd1.x + surd2.x, surd2.y, surd2.r);
	}
	if (surd2.r == 0) {	
		return Surd(surd1.x + surd2.x, surd1.y, surd1.r);
	}
	return Surd(surd1.x + surd2.x, surd1.y + surd2.y, surd1.r);
};

Surd Surd::operator-() {
	if (NS) {
		Surd s(0, 0, 0);
		s.NS = true;
		return s;
	}
	return Surd(-x, -y, r);
};

Surd operator-(const Surd &s1, const Surd &s2) {
	return Surd(s1) + (-Surd(s2));
};

Surd operator*(const Surd &s1, const Surd &s2) {
	if (s1.NS || s2.NS) {
		Surd s(0, 0, 0);
		s.NS = true;
		return s;
	}
	Surd surd1 = evaluate(s1), surd2 = evaluate(s2);
	if (surd1.r != surd2.r && surd1.y != 0 && surd2.y!=0 && (surd1.x != 0 || surd1.x != 0)) {
		Surd s(0, 0, 0);
		s.NS = true;
		return s;
	}
	if (surd1.y == 0) {
		return Surd(surd1.x*surd2.x, surd1.x*surd2.y, surd2.r);
	}
	if (surd2.y == 0) {
		return Surd(surd1.x*surd2.x, surd2.x*surd1.y, surd1.r);
	}
	if (surd1.x == 0 && surd2.x == 0) {
		if (surd1.r < 0 && surd2.r < 0) {
			return Surd(0, -surd1.y*surd2.y, surd1.r*surd2.r);
		}
		return Surd(0, surd1.y*surd2.y, surd1.r*surd2.r);
	}
	return Surd(surd1.x*surd2.x + surd1.y*surd2.y*surd1.r, surd1.x*surd2.y + surd2.x*surd1.y, surd1.r);
};

Surd Surd::operator~() {
	if (NS) {
		Surd s(0, 0, 0);
		s.NS = true;
		return s;
	}
	return Surd(x, -y, r);
};

int Surd::operator*() {
	if (NS) {
		Surd s(0, 0, 0);
		s.NS = true;
		return s;
	}
	return evaluate(Surd(x, y, r)*(~Surd(x, y, r))).x;
};

Surd Surd::operator^(const unsigned n) {
	if (NS) {
		Surd s(0, 0, 0);
		s.NS = true;
		return s;
	}
	unsigned br = 1;
	Surd s(x, y, r);
	while (br < n) {
		s = s*Surd(x, y, r);
		br++;
	}
	return s;
};