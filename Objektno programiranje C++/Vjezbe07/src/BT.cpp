/*
 * BT.cpp
 *
 *  Created on: 15. tra 2015.
 *      Author: Tomislav
 */

#include "BT.h"

void Segment::refine() {
	if (isLeaf()) {
		const double middle = (mpt_l + mpt_r) / 2;
		mseg_l.reset(new Segment(mpt_l, middle, this));
		mseg_r.reset(new Segment(middle, mpt_r, this));
	}
}
// Okrupni segment, tj. eliminiraj djecu segmenta. Time segment postaje
// list. Segment mora imati djecu koja su listovi, u suprotnom izbaciti izuzetak.
void Segment::coarse() {
	if (isLeaf()) {
		throw std::domain_error("Segmint is leaf and it can not be coarsed.");
	}
	if (!getLeft()->isLeaf() || !getRight()->isLeaf()) {
		throw std::domain_error(
				"Segment's children have to be leafs for segment to be coarsed.");
	}
	mseg_l.release();
	mseg_r.release();
}

GridLeafIterator::GridLeafIterator(const GridLeafIterator & it) :
		mRoot(it.mRoot) {
	//std::cout<<"C-CTor"<<std::endl;
}
GridLeafIterator::GridLeafIterator(GridLeafIterator && it) {
	//std::cout<<"M-CTor"<<std::endl;
	if (this != &it) {
		mRoot = std::move(it.mRoot);
	}
}
GridLeafIterator& GridLeafIterator::operator=(const GridLeafIterator & it) {
	//std::cout<<"OP"<<std::endl;
	if (this != &it) {
		mRoot = it.mRoot;
	}
	return *this;
}
GridLeafIterator& GridLeafIterator::operator=(GridLeafIterator && it) {
	//std::cout<<"M-OP"<<std::endl;
	if (this != &it) {
		mRoot = std::move(it.mRoot);
	}
	return *this;
}

Grid::iterator Grid::begin() {
	Segment *current = &root;
	while (!current->isLeaf()) {
		current = current->getLeft();
	}
	return iterator(current);
}

Grid::iterator Grid::end() {
	return iterator(nullptr);
}

// Profini svaki segment list u trenutnoj mreži.
void Grid::uniform_refine() {
	for (iterator it = begin(), last = end(); it != last; ++it) {
		it->refine();
	}
}
// Ispiši sve segmente listove mreže.
void Grid::print() {
	bool notFirst = false;
	for (iterator it = begin(), last = end(); it != last; ++it) {
		if (notFirst) {
			std::cout << " - ";
		}
		it->print();
	}
}

// Broj segmenata listova u mreži.
int Grid::nOfSegments() { // Ne može biti konstantna jer nemamo konstantan iterator
	int n = 0;
	GridLeafIterator it = begin(), end_it = end();
	for (; it != end_it; ++it) {
		n++;
	}
	return n;
}

GridLeafIterator Grid::getIthLeaf(int noSeg) {
	int pos = 0;
	GridLeafIterator it = begin(), iend = end();
	for (; pos < noSeg && it != iend; ++it, ++pos) {
	}
	if (it == iend) {
		throw new std::out_of_range("Segment doesn't exist.");
	}
	return it;
}

// Profini segment list koji je noSeg po redu.
// Ako je noSeg >=  nOfSegments() izbaci izuzetak
void Grid::refine_selected(int noSeg) {
	getIthLeaf(noSeg)->refine();
}
// Eliminiraj  segment list koji je noSeg po redu ukoliko
// su oba djeteta njegovog roditelja listovi.
void Grid::coarse_selected(int noSeg) {
	GridLeafIterator it = getIthLeaf(noSeg);
	// provjera da ne baci iznimku jer u specifikaciji ne pise da treba.
	if (it->parent()->getLeft()->isLeaf()
			&& it->parent()->getRight()->isLeaf()) {
		it->parent()->coarse();
	}
}

GridLeafIterator& GridLeafIterator::operator++() {
	if (mRoot == nullptr) {
		throw std::overflow_error(
				"Can not reach past the end of the operator.");
	}
	Segment *old = mRoot;
	mRoot = mRoot->mparent;
	while (mRoot != nullptr && mRoot->getLeft() != old) {
		old = mRoot;
		mRoot = mRoot->mparent;
	}
	if (mRoot != nullptr) {
		mRoot = mRoot->getRight();
		while (!mRoot->isLeaf()) {
			mRoot = mRoot->getLeft();
		}
	}
	return *this;
}

GridLeafIterator GridLeafIterator::operator++(int) {
	GridLeafIterator old(*this);
	++*this;
	return old;
}

bool operator==(GridLeafIterator const & lhs, GridLeafIterator const & rhs) {
	return lhs.mRoot == rhs.mRoot;
}
bool operator!=(GridLeafIterator const & lhs, GridLeafIterator const & rhs) {
	return !(lhs.mRoot == rhs.mRoot);
}
