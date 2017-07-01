/*
 * allPairsShortestPath.cpp
 *
 *  Created on: 11. 3. 2015.
 *      Author: Tomislav
 */
#include "allPairsShortestPath.h"

double calculatePathLength(std::vector<tocka> & tocke) {
	double pathLength = 0;
	bool notFirst = false;
	tocka last;
	for (tocka t : tocke) {
		if (notFirst) {
			pathLength += t.distance(last);
		} else {
			notFirst = true;
		}
		last = t;
	}
	return pathLength;
}

double calculatePathLength(std::vector<tocka*> & tocke) {
	double pathLength = 0;
	bool notFirst = false;
	tocka* last;
	for (tocka* t : tocke) {
		if (notFirst) {
			pathLength += t->distance(*last);
		} else {
			notFirst = true;
		}
		last = t;
	}
	return pathLength;
}

bool pathContains(std::vector<tocka*> & path, tocka & t) {
	for (tocka* tocka : path) {
		if (*tocka == t) {
			return true;
		}
	}
	return false;
}

void copyWithoutPointers(std::vector<tocka*> & from, std::vector<tocka> & to) {
	to.clear();
	for (tocka* t : from) {
		to.push_back(*t);
	}
}

void shortestPathRecursion(std::vector<tocka> & tocke,
		std::vector<tocka> & shortestPath, double *bestPathLength, std::vector<tocka*> & currentPath) {
	bool notEqualLength = currentPath.size() + 1 < tocke.size();
	for (tocka t : tocke) {
		if (!pathContains(currentPath, t)) {
			currentPath.push_back(&t);
			if (notEqualLength) {
				shortestPathRecursion(tocke, shortestPath, bestPathLength, currentPath);
			} else {
				double currentPathLength = calculatePathLength(currentPath);
				if (*bestPathLength < 0) {
					*bestPathLength = currentPathLength;
					copyWithoutPointers(currentPath, shortestPath);
				} else {
					 if (*bestPathLength > currentPathLength) {
						 *bestPathLength = currentPathLength;
						 copyWithoutPointers(currentPath, shortestPath);
					 }
				}
				currentPath.pop_back();
				return;
			}
			currentPath.pop_back();
		}
	}
}

void findShortestPathRecursive(std::vector<tocka> & tocke,
		std::vector<tocka> & shortestPath, double *bestPathLength) {
	std::vector<tocka*> currentPath;
	shortestPathRecursion(tocke, shortestPath, bestPathLength, currentPath);
}

void findShortestPathNonrecursive(std::vector<tocka> & tocke,
		std::vector<tocka> & shortestPath, double *pathLength) {
	std::sort(tocke.begin(), tocke.end());
	bool notFirst = false;
	while (std::next_permutation(tocke.begin(), tocke.end())) {
		if (notFirst) {
			double currentPathLength = calculatePathLength(tocke);
			if (*pathLength > currentPathLength) {
				*pathLength = currentPathLength;
				shortestPath = std::vector<tocka>(tocke);
			}
		} else {
			notFirst = true;
			*pathLength = calculatePathLength(tocke);
			shortestPath = std::vector<tocka>(tocke);
		}
	}
}
