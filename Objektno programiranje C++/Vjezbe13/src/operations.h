/*
 * operations.h
 *
 *  Created on: Jun 10, 2015
 *      Author: tomislav
 */

#ifndef SRC_OPERATIONS_H_
#define SRC_OPERATIONS_H_

#include <array>
#include <ostream>

//////////////////////////////////////////////
//////////////////Scalar: ///////////////////
////////////////////////////////////////////

class Scalar {
private:
	double const & val;
public:
	Scalar(double const& v) :
			val(v) {
	}
	double operator[](size_t) const {
		return val;
	}

	friend std::ostream & operator<<(std::ostream &, Scalar const &);
};

std::ostream & operator<<(std::ostream & out, Scalar const & scalar) {
	out << scalar.val;
	return out;
}

//////////////////////////////////////////////
//////////////////Vector: ///////////////////
////////////////////////////////////////////

template<size_t N, typename Rep = std::array<double, N> >
class Vector {
private:
	Rep expr_rep;  // Implementacijski objekt
public:
	// Konstruktor inicijalizira implementacijski objekt
	Vector(Rep const& r) :
			expr_rep(r) {
	}
	// Vektor možemo inicijalizirati konstantom.
	explicit Vector(double val = 0.0) {
		expr_rep.fill(val);
	}
	// pridruživanje polja različitog tipa
	template<typename Rep2>
	Vector& operator=(Vector<N, Rep2> const& rhs) {
		for (size_t i = 0; i < N; ++i) {
			expr_rep[i] = rhs[i];
		}
		return *this;
	}
	// Pomoćne funkcije
	size_t size() const {
		return N;
	}
	double operator[](size_t i) const {
		return expr_rep[i];
	}
	double& operator[](size_t i) {
		return expr_rep[i];
	}
	Rep const& rep() const {
		return expr_rep;
	}
	Rep& rep() {
		return expr_rep;
	}
};

template<size_t N, typename R>
std::ostream & operator<<(std::ostream & out, Vector<N, R> const & vector) {
	out << vector.rep();
	return out;
}

template<size_t N>
std::ostream & operator<<(std::ostream & out,
		std::array<double, N> const & array) {
	out << "Array<" << N << ">";
	return out;
}

//////////////////////////////////////////////
//////////////////Traits: ///////////////////
////////////////////////////////////////////

// Klasa obilježja koja nam omogućava vektor tretiramo kroz
// reference, a skalare po vrijednosti.
template<typename T>
struct Traits {
	using ExprRef = T const &;
};
// Specijalizacija za skalare
// Na skalare ne uzimamo referencu jer im vijek trajanja može biti kraći od
// vijeka trajanja vektora
template<>
struct Traits<Scalar> {
	using ExprRef = Scalar;
};

//////////////////////////////////////////////
//////////////////Addition: /////////////////
////////////////////////////////////////////

template<typename OP1, typename OP2>
class Add;

template<typename OP1, typename OP2>
std::ostream & operator<<(std::ostream &, Add<OP1, OP2> const &);

// Klasa koja reprezentira zbrajanje.
template<typename OP1, typename OP2>
class Add {
private:
	typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
public:
	Add(OP1 const& a, OP2 const& b) :
			op1(a), op2(b) {
	}
	double operator[](int i) const {
		return op1[i] + op2[i];
	}
	friend std::ostream & operator<<<>(std::ostream &, Add const &);
};

// Zbrajanje vektora
template<size_t N, typename R1, typename R2>
Vector<N, Add<R1, R2> > operator+(Vector<N, R1> const& a,
		Vector<N, R2> const& b) {
	return Vector<N, Add<R1, R2> >(Add<R1, R2>(a.rep(), b.rep()));
}

// Zbrajanje skalar - vektor
template<size_t N, typename R2>
Vector<N, Add<Scalar, R2> > operator+(double const& a, Vector<N, R2> const& b) {
	return Vector<N, Add<Scalar, R2> >(Add<Scalar, R2>(Scalar(a), b.rep()));
}

// Zbrajanje vektor - skalar
template<size_t N, typename R2>
Vector<N, Add<R2, Scalar> > operator+(Vector<N, R2> const& a, double const& b) {
	return Vector<N, Add<R2, Scalar> >(Add<R2, Scalar>(a.rep(), Scalar(b)));
}

template<typename OP1, typename OP2>
std::ostream & operator<<(std::ostream & out, Add<OP1, OP2> const & add) {
	out << "Add<" << add.op1 << "," << add.op2 << ">";
	return out;
}

//////////////////////////////////////////////
/////////////////Subtraction: ///////////////
////////////////////////////////////////////

template<typename OP1, typename OP2>
class Sub;

template<typename OP1, typename OP2>
std::ostream & operator<<(std::ostream &, Sub<OP1, OP2> const &);

// Klasa koja reprezentira oduzimanje.
template<typename OP1, typename OP2>
class Sub {
private:
	typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
public:
	Sub(OP1 const& a, OP2 const& b) :
			op1(a), op2(b) {
	}
	double operator[](int i) const {
		return op1[i] - op2[i];
	}
	friend std::ostream & operator<<<>(std::ostream &, Sub const &);
};

// Oduzimanje vektora
template<size_t N, typename R1, typename R2>
Vector<N, Sub<R1, R2> > operator-(Vector<N, R1> const& a,
		Vector<N, R2> const& b) {
	return Vector<N, Sub<R1, R2> >(Sub<R1, R2>(a.rep(), b.rep()));
}

// Oduzimanje skalar - vektor
template<size_t N, typename R2>
Vector<N, Sub<Scalar, R2> > operator-(double const& a, Vector<N, R2> const& b) {
	return Vector<N, Sub<Scalar, R2> >(Sub<Scalar, R2>(Scalar(a), b.rep()));
}

// Oduzimanje vektor - skalar
template<size_t N, typename R2>
Vector<N, Sub<R2, Scalar> > operator-(Vector<N, R2> const& a, double const& b) {
	return Vector<N, Sub<R2, Scalar> >(Sub<R2, Scalar>(a.rep(), Scalar(b)));
}

template<typename OP1, typename OP2>
std::ostream & operator<<(std::ostream & out, Sub<OP1, OP2> const & sub) {
	out << "Sub<" << sub.op1 << "," << sub.op2 << ">";
	return out;
}

//////////////////////////////////////////////
///////////////Multiplication: //////////////
////////////////////////////////////////////

template<typename OP1, typename OP2>
class Mult;

template<typename OP1, typename OP2>
std::ostream & operator<<(std::ostream &, Mult<OP1, OP2> const &);

// Klasa koja reprezentira mnozenje.
template<typename OP1, typename OP2>
class Mult {
private:
	typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
public:
	Mult(OP1 const& a, OP2 const& b) :
			op1(a), op2(b) {
	}
	double operator[](int i) const {
		return op1[i] * op2[i];
	}
	friend std::ostream & operator<<<>(std::ostream &, Mult const &);
};

// Množenje vektora
template<size_t N, typename R1, typename R2>
Vector<N, Mult<R1, R2> > operator*(Vector<N, R1> const& a,
		Vector<N, R2> const& b) {
	return Vector<N, Mult<R1, R2> >(Mult<R1, R2>(a.rep(), b.rep()));
}

// Množenje skalar * vektor
template<size_t N, typename R2>
Vector<N, Mult<Scalar, R2> > operator*(double const& a,
		Vector<N, R2> const& b) {
	return Vector<N, Mult<Scalar, R2> >(Mult<Scalar, R2>(Scalar(a), b.rep()));
}

// Množenje vektor * skalar
template<size_t N, typename R2>
Vector<N, Mult<R2, Scalar> > operator*(Vector<N, R2> const& a,
		double const& b) {
	return Vector<N, Mult<R2, Scalar> >(Mult<R2, Scalar>(a.rep(), Scalar(b)));
}

template<typename OP1, typename OP2>
std::ostream & operator<<(std::ostream & out, Mult<OP1, OP2> const & mult) {
	out << "Mult<" << mult.op1 << "," << mult.op2 << ">";
	return out;
}

#endif /* SRC_OPERATIONS_H_ */
