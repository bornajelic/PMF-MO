
#include <map>
#include <utility>
#include <list>
#include "graf.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

void ispisMape(map<pair<string, string>, int> p){
	for(map<pair<string, string>, int>::iterator i=p.begin();i!=p.end();i++)
		cout << i->first.first<<" - "<<i->first.second<<" "<< i->second<<" ";
	cout<<endl;
}

void ispisListe(list<string> p){
	for(list<string>::iterator i=p.begin();i!=p.end();i++) cout << *i <<" ";
		cout<<endl;
}

void ispisSkupa(set<string> p){
	for(set<string>::iterator i=p.begin();i!=p.end();i++) cout << *i <<" ";
		cout<<endl;
}

int main(void) {
	graf test;
	test.dodaj("a","b",30); test.dodaj("a","c",40); test.dodaj("a","g",60);
	test.dodaj("b","d",110); test.dodaj("a","d",160); test.dodaj("f","g",45);
	test.dodaj("g","g",120); test.dodaj("g","a",40);test.dodaj("g","a",40);
	test.dodaj("a","b",40);test.dodaj("c","a",40);test.dodaj("e","a",40);
	
	test.ukloni("f", "g");
	
	//cout<<test.stupanj1("a")<<"        "<<test.stupanj2("d")<<endl;
	
	//ispisListe(test.vrhovi());

	//cout<<test.najlaksiBridTeziOd(50).first<<" "<<test.najlaksiBridTeziOd(50).second<<endl;
	ispisSkupa(test.dohvatljiviIz("a"));
}
