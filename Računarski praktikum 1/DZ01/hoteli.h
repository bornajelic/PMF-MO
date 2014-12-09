#pragma once

#include <string>

class Hotel {
	string ime;
	string grad;
	int cijena;
	int brojSlobodnihMjesta;
	
	Hotel (string ime,string grad, int cijena, int brojSlobodnihMjesta);
	string Ime(void);
	string Grad(void);
	int Cijena(void);
	int BrojSlobodnihMjesta(void);
	int Jednaki (Hotel h1)
}

class SkupHotela {
	Hotel hotel[100];
	int brojClanova;

	//konstruktor, deafult
	SkupHotela() {
		hotel=new Hotel[100];
	}
	
	//konstruktor, sa imenom hotela
	SkupHotela(Hotel h){
		SkupHotela();
		hotel[0]=h;
	}
	void Dodaj(Hotel h);
	void Izbaci(Hotel h);
	int Izbaci(Hotel h);
	int BrojHotela(void);
	Hotel ItiHotel(int i);
	SkupHotela NadjiHoteleUGradu(string grad);
	SkupHotela NadjiHotele(string grad, int maxCijena, int minSlobodnihMj);
	int NajmanjaCijenaUGradu(string grad);
	void SortirajPoCijeni(void);
}