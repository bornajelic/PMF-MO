#include "graf.h"
using namespace std;
/**
 *  ubacuje par u mapu ako je razlicitih bridova i ako vec ne postoji
 */
void graf::dodaj(string p, string d, int n) {
	bool trebaUbaciti = true;
	if (p != d) {
		map<pair<string, string>, int>::iterator si;
		//iterira po listi i trazi postoje li
		for (si = bridovi.begin(); si != bridovi.end(); si++) {
			if (si->first.first == p && si->first.second == d) {
				trebaUbaciti = false;
			}
		}
	} else {
		trebaUbaciti = false;
	}
	if (trebaUbaciti) {
		bridovi.insert (pair<pair<string, string>, int> (pair<string, string> (p, d), n));
	}
	
};
/**
 *  brise brid (s,p)
 */
void graf::ukloni(string p, string d) {
	map<pair<string, string>, int>::iterator si = bridovi.begin();
	while (si != bridovi.end()) {
		if (si->first.first == p && si->first.second == d) {
			bridovi.erase(si);
			si = bridovi.end();
		} else {
			si++;
		}
	}
	/*
	for (si = bridovi.begin(); si != bridovi.end(); ) {
		if (si->first.first == p && si->first.second == d) {
			map<pair<string, string>, int>::iterator stemp = si;
			stemp++;
			bridovi.erase(si);
			si = stemp;
		} else {
			si++;
		}
	}*/
};
/**
 *  vraca broj bridova sa vrh kao polaznom tockom
 */
int graf::stupanj1(string vrh) {
	int counter = 0;
	map<pair<string, string>, int>::iterator si;
	for (si = bridovi.begin(); si != bridovi.end(); si++) {
		if (si->first.first == vrh) {
			counter ++;
		}
	}
	return counter;
};
/**
 *  vraca broj bridova sa vrh kao zavrsnom tockom
 */
int graf::stupanj2(string vrh) {
	int counter = 0;
	map<pair<string, string>, int>::iterator si;
	for (si = bridovi.begin(); si != bridovi.end(); si++) {
		if (si->first.second == vrh) {
			counter ++;
		}
	}
	return counter;
};

/**
* trazi postoji li element u listi
*/
bool sadrziElement(list<string> l, string s) {
	list<string>::iterator li = l.begin();
	while(li != l.end()) {
		if (*li == s) {
			return true;
		}
		li++;
	}
	return false;
}


list<string> graf::vrhovi() {
	list<string> lista;
	map<pair<string, string>, int>::iterator si;
	for (si = bridovi.begin(); si != bridovi.end(); si++) {
		if (!sadrziElement(lista, si->first.first)) {
			lista.push_back(si->first.first);
		}
		if (!sadrziElement(lista, si->first.second)) {
			lista.push_back(si->first.second);
		}
	}
	return lista;
};

pair<string, string> graf::najlaksiBridTeziOd(int c) {
	map<pair<string, string>, int>::iterator si = bridovi.begin();
	pair<string, string> par;
	bool postoji = false;
	int tezina = 0;
	for (si; si != bridovi.end(); si++) {
		if (si->second > c) {
			if (!postoji) {
				par = si->first;
				tezina = si->second;
				postoji = true;
			} else if (tezina > si->second) {
				par = si->first;
				tezina = si->second;
			}
		}
	}
	return par;
};

void popuni(set<string> *dohvatljivi, string vrh, map<pair<string, string>, int> bridovi) {
	map<pair<string, string>, int>::iterator si = bridovi.begin();
	for (si; si != bridovi.end(); si++) {
		if (vrh == si->first.first && !(*dohvatljivi).count(si->first.second)) {
			(*dohvatljivi).insert(si->first.second);
			popuni(dohvatljivi, si->first.second, bridovi);
		}
	}
};

set<string> graf::dohvatljiviIz(string vrh) {
	set<string> dohvatljivi;
	map<pair<string, string>, int>::iterator si = bridovi.begin();
	if (si != bridovi.end()) {
		for (si; si != bridovi.end(); si++) {
			if (si->first.first == vrh) {
				dohvatljivi.insert(si->first.second);
				popuni(&dohvatljivi, si->first.first, bridovi);
			}
		}
	}
	return dohvatljivi;
};
