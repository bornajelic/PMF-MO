#include <iostream>
#include<cmath>
#include<string>

using namespace std;

class Surd {
private:
	int x, y, r;
	bool NS;
	friend Surd evaluate(const Surd surd);
	Surd(bool ns);
public:
	Surd();
	Surd(int x);
	Surd(int x, int y, int r);
	static Surd NaS;

	operator double()const;
	friend ostream& operator<<(ostream& f, const Surd surd);
	int& operator++();
	int& operator++( int );
	int const& operator++() const;
	int const& operator++( int ) const;
	friend bool operator==(const Surd &s1, const Surd &s2);
	friend bool operator<(const Surd &s1, const Surd &s2);
	friend Surd operator+(const Surd &s1, const Surd &s2);
	friend Surd operator-(const Surd &s1, const Surd &s2);
	friend Surd operator*(const Surd &s1, const Surd &s2);
	Surd operator-();
	Surd operator~();
	int operator*();
	Surd operator^(const unsigned n);
};