/*
 * BT.h
 *
 *  Created on: 15. tra 2015.
 *      Author: Tomislav
 */

#ifndef BT_H_
#define BT_H_

#include <memory>
#include <iostream>
#include <stdexcept>
#include <utility>

//class GridLeafIterator;
class Segment {
public:
	// Konstruktor. Postavlja lijevi i desni kraj intervala i pokazivaè na roditelja.
	Segment(double left, double right, Segment * parent) :
			mpt_l(left), mpt_r(right), mparent(parent) {
		if (left > right) {
			throw std::invalid_argument("Left can not be bigger than right.");
		}
	}
	// Da li je segment list (nema djece) ?
	bool isLeaf() const {
		return mseg_l.get() == nullptr;
	}
	// Profini segment. Ako veæ ima djecu ne radi ništa.
	void refine();
	// Okrupni segment, tj. eliminiraj djecu segmenta. Time segment postaje
	// list. Segment mora imati djecu koja su listovi, u suprotnom izbaciti izuzetak.
	void coarse();
	// Lijevi podsegment ili nullptr.
	Segment* getLeft() {
		return mseg_l.get();
	}
	// Desni podsegment ili nullptr.
	Segment* getRight() {
		return mseg_r.get();
	}
	// Ispiši segment.
	void print() {
		std::cout << "(" << mpt_l << "," << mpt_r << ") ";
	}
	// Vrati pokazivaè na roditelja.
	Segment* parent() {
		return mparent;
	}
private:
	// lijevi kraj segmenta
	double mpt_l;
	// desni kraj segmenta
	double mpt_r;
	// djeca segementa
	std::unique_ptr<Segment> mseg_l;  // lijevi podsegment
	std::unique_ptr<Segment> mseg_r;  // desni podsegment
	// segment roditelj
	Segment * mparent;
	friend class GridLeafIterator;
};

class GridLeafIterator;
class Grid {
public:
	using iterator = GridLeafIterator;

	Grid(double a, double b) :
			root(a, b, nullptr) {
	}
	iterator begin();
	iterator end();

	// Profini svaki segment list u trenutnoj mreži.
	void uniform_refine();
	// Ispiši sve segmente listove mreže.
	void print();
	// Broj segmenata listova u mreži.
	int nOfSegments();
	// Profini segment list koji je noSeg po redu.
	// Ako je noSeg >=  nOfSegments() izbaci izuzetak
	void refine_selected(int noSeg);
	// Eliminiraj  segment list koji je noSeg po redu ukoliko
	// su oba djeteta njegovog roditelja listovi.
	void coarse_selected(int noSeg);

private:
	GridLeafIterator getIthLeaf(int noSeg);
	Segment root;
};

// Iterator koji iterira samo po djeci listovima mreže (segmentima koji nemaju djecu).
class GridLeafIterator {
public:
	GridLeafIterator(Segment *root) :
			mRoot(root) {
		//std::cout<<"CTor"<<std::endl;
	}
	GridLeafIterator(const GridLeafIterator & it);
	GridLeafIterator(GridLeafIterator && it);
	GridLeafIterator& operator=(const GridLeafIterator & it);
	GridLeafIterator& operator=(GridLeafIterator && it);

	GridLeafIterator& operator++(); //prefiks
	GridLeafIterator operator++(int); //postfiks

	Segment* operator->() {
		return mRoot;
	}
	Segment& operator*() {
		return *mRoot;
	}
private:
	Segment *mRoot;
	friend
	bool operator==(GridLeafIterator const & lhs, GridLeafIterator const & rhs);
	friend
	bool operator!=(GridLeafIterator const & lhs, GridLeafIterator const & rhs);
};
bool operator==(GridLeafIterator const & lhs, GridLeafIterator const & rhs);
bool operator!=(GridLeafIterator const & lhs, GridLeafIterator const & rhs);

#endif /* BT_H_ */
