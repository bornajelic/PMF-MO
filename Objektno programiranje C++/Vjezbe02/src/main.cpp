#include <iostream>
#include <set>
#include <vector>
#include "tocka.h"
#include "allPairsShortestPath.h"

void ispisi(std::vector<tocka> & tocke) {
	bool notFirst = false;
	for (tocka t : tocke) {
		if (notFirst) {
			std::cout << ", ";
		} else {
			notFirst = true;
		}
		t.ispisi();
	}
	std::cout << std::endl;
}

int main(void) {

	int n;
	std::cin >> n;

	double a, b;
	std::vector<tocka> tocke;
	for (int i = 0; i < n; ++i) {
		std::cin >> a >> b;
		tocke.push_back(tocka(a, b));
	}

	std::cout << "Unjeli ste tocke:" << std::endl;
	ispisi(tocke);

	std::vector<tocka> rjRekurzivno, rjIterativno;
	double recursiveLength = -1, nonrecursiveLength;
	findShortestPathRecursive(tocke, rjRekurzivno, &recursiveLength);
	findShortestPathNonrecursive(tocke, rjIterativno, &nonrecursiveLength);

	std::cout << "Rekurzivno (put je dugacak " << recursiveLength << "):" << std::endl;
	ispisi(rjRekurzivno);
	std::cout << "Nerekurzivno (put je dugacak " << nonrecursiveLength << "):" << std::endl;
	ispisi(rjIterativno);

	return 0;
}
