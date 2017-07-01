/*
 * Vect.cpp
 *
 *  Created on: 1. tra 2015.
 *      Author: Tomislav
 */

#include "Vect.h"
#include <cmath>

// konstruktor i delegirajuæe verzije
Vect::Vect(size_t n, double v, std::string const & ime) :
		ime(ime), mdata(nullptr), mfirst_free(nullptr), mend(nullptr) { // Ctor
//	mdata = alloc.allocate(n);
//	alloc.construct(mdata, v);
//	mfirst_free = mdata + 1;
//	mend = mdata + n;
	std::cerr << "Ctor" << std::endl;
	if (n > 0) {
		mdata = alloc.allocate(n);
		for (size_t i = 0; i < n; ++i) {
			alloc.construct(mdata + i, v);
		}
		mfirst_free = mend = mdata + n;
	}
}
// Kontrola kopiranja
Vect::Vect(const Vect& v) :
		ime(v.ime) { //CCtor
	std::cerr << "CCtor" << std::endl;
	copy_vect_to_this(v);
}

Vect::Vect(Vect && v) noexcept :
ime(std::move(v.ime)), mdata(v.mdata), mfirst_free(
		v.mfirst_free), mend(v.mend) {                       // MCtor
	std::cerr << "MCtor" << std::endl;
	v.mdata = nullptr;
	v.mend = nullptr;
	v.mfirst_free = nullptr;
}

Vect& Vect::operator=(const Vect& v) {                // OP
	std::cerr << "OP" << std::endl;
	if (this != &v) {
		ime = v.ime;
		free();
		copy_vect_to_this(v);
	}
	return *this;
}

void Vect::copy_vect_to_this(const Vect& v) {
	if (v.mdata == nullptr) {
		mdata = nullptr;
		mend = nullptr;
		mfirst_free = nullptr;
	} else {
		mdata = alloc.allocate(v.capacity());
		mend = mdata + v.capacity();
		mfirst_free = mdata + v.size();
		// std::cout<<"old: ";v.print(std::cout); std::cout<<std::endl;///
		for (double *p = mdata, *p_v = v.mdata; p < mfirst_free; ++p, ++p_v) {
			alloc.construct(p, *p_v);
		}
		// std::cout<<"new: ";print(std::cout);  std::cout<<std::endl;
	}
}

Vect& Vect::operator=(Vect && v) noexcept {            // MOP
	std::cerr << "MOP" << std::endl;
	if (this != &v) {
		mdata = v.mdata;
		v.mdata = nullptr;
		ime = std::move(v.ime);
		mend = v.mend;
		v.mend = nullptr;
		mfirst_free = v.mfirst_free;
		v.mfirst_free = nullptr;
	}
	return *this;
}

// push_back kao u std::vector. Eventualno izaziva realokaciju èitavog vektora
void Vect::push_back(double new_element) {
//	if (mfirst_free == mend) {
//		reallocate();
//	}
//	*mfirst_free = new_element;
//	mfirst_free++;
	if (!has_space()) {
		reallocate();
	}
	alloc.construct(mfirst_free++, new_element);
}

// utility-rutine
double Vect::norm2() const {
	double norm = 0;
	for (double *p = mdata; p != mfirst_free; ++p) {
		norm += ((*p) * (*p));
	}
	return std::sqrt(norm);
}
Vect& Vect::scale(double alpha) {
	for (double *p = mdata; p != mfirst_free; ++p) {
		(*p) *= alpha;
	}
	return *this;
}
void Vect::print(std::ostream& out) const {
//	bool notFirst = false;
//	out << "(";
//	for (double *p = mdata; p != mfirst_free; ++p) {
//		if (notFirst) {
//			out << ", ";
//		}
//		out << *p;
//	}
//	out << ")";
	out << ime << ": (" << size() << "," << capacity() << ") ";
	for (size_t i = 0; i < size(); ++i) {
		out << mdata[i];
		if (i + 1 < size())
			out << ",";
	}
}

// Oslobodi zauzeti prostor (pomoæu alokatora)
void Vect::free() {
	if (mdata != nullptr) {
		for (double *p = mdata; p < mfirst_free; ++p) {
			alloc.destroy(p);
		}
		alloc.deallocate(mdata, capacity());
		mdata = nullptr;
	}
	mfirst_free = nullptr;
	mend = nullptr;
}
// realociraj na novu lokaciju. Poveæaj dimenziju vektora 2 puta; ako je
// vektor prazan dodaj jedan element.
void Vect::reallocate() {
	double *newData, *newEnd, *newFristFree;
	if (mdata == nullptr || capacity() == 0) {
		newData = alloc.allocate(1);
		newEnd = newData + 1;
	} else {
		newData = alloc.allocate(capacity() * 2);
		newEnd = newData + 2 * size();
	}
//	if (size() == 0) { // vektor prazan dodaj jedan element.
//		alloc.construct(newData, 0.0);
//		newFristFree = newData + 1;
//	} else {
//		for (double *p_new = newData, *p_old = mdata; p_old < mend;
//				++p_new, ++p_old) {
//			alloc.construct(p_new, *p_old);
//		}
//		newFristFree = newData + size();
//	}
	for (double *p_new = newData, *p_old = mdata; p_old < mend;
			++p_new, ++p_old) {
		alloc.construct(p_new, *p_old);
	}
	newFristFree = newData + size();

	free();
	mend = newEnd;
	mfirst_free = newFristFree;
	mdata = newData;
}

// alokator ne mora imati pristup varijablama èlanicama klase pa ga èinimo
// statièkim. Ne zaboraviti definirati ga u izvornoj datoteci.
std::allocator<double> Vect::alloc;
