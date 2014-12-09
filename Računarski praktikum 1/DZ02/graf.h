#include <map>
#include <utility>
#include <list>
#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

struct graf {
	map<pair<string, string>, int> bridovi;
	void dodaj(string p, string d, int n);
	void ukloni(string p, string d);
	int stupanj1(string p);
	int stupanj2(string p);
	list<string> vrhovi();
	pair<string, string> najlaksiBridTeziOd(int c);
	set<string> dohvatljiviIz(string s);
};
