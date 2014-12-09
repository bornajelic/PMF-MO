#include "hoteli.h"

#include<iostream>
#include<string>

	
Hotel Hotel::(string _ime,string _grad, int _cijena, int _brojSlobodnihMjesta) {
	ime=_ime;
	grad=_grad;
	cijena=_cijena;
	brojSlobodnihMjesta=_brojSlobodnihMjesta;
}

string Hotel::Ime(void) {
	return ime;
}

string Hotel::Grad(void) {
	return grad;
}

int Hotel::Cijena(void){
	return cijena;
}

int Hotel::BrojSlobodnihMjesta() {
	return brojSlobodnihMjesta;
}

int Hotel::Jednaki (Hotel h1){
	if ((ime==h1.Ime)&&(grad==h1.Grad)&&(cijena==h1.Cijena)&&(brojSlobodnihMjesta==hr.BrojSlobodnihMjesta))
		return 1;
	else
		return 0;
}







SkupHotela::SkupHotela() {
	brojClanova=0;
}



SkupHotela::SkupHotela(Hotel h) {
	hotel[0]=h;
	brojClanova=1;
}

void SkupHotela::Dodaj(Hotel h) {
	hotel[brojClanova++]=h;
}

void SkupHotela::Izbaci(Hotel h) {
	int izbacenih=0;
	
	for (int i=0;i<brojClanova;++i) {
		Hotel trenutni=hotel[i];
		
		if (izbacenih)
			hotel[i-izbacenih]=hotel[i];
			
		if (h.Jednaki(trenutni) {
			izbacenih++;
			brojClanova--;
		}
	}

}


int SkupHotela::BrojHotela(void) {
	return brojClanova;
}

Hotel SkupHotela::ItiHotel(int i) {
	return hotel[i];
}


SkupHotela SkupHotela::NadjiHoteleUGradu(string grad) {
	SkupHotela uGradu=new SkupHotela();
	
	for (int i=0; i<brojClanova;++i)
		if (hotel[i].Grad()==grad)
			uGradu.Dodaj(hotel[i]);
			
	return uGradu;
}

SkupHotela SkupHotela::NadjiHotele(string grad, int maxCijena, int minSlobodnihMj) {
	SkupHotela rjesenje=new SkupHotela();
	
	for (int i=0;i<brojClanova;++i)
		if (hotel[i].Grad()=grad)&&(hotel[i].Cijena()<=maxCijena)&&(hotel[i].BrojSlobodnihMjesta()>=minSlobodnihMj)
			rjesenje.Dodaj(hotel[i]);
			
	return rjesenje;
}

int SkupHotela::NajmanjaCijenaUGradu(string grad){
	SkupHotela rjesenje=this.NadjiHoteleUGradu(grad);
	
	int brojHotela=rjesenje.BrojHotela();
	if(!brojHotela)
		return -1;
	
	int	najmanjaCijena=ItiHotel(0).Cijena();
	for (int i=0;i<brojHotela;++i);
		if ((cijena=ItiHotel(i).Cijena())<najmanjaCijena)
			najmanjaCijena=cijena;
	
	return najmanjaCijena;

}

void SkupHotela::SortirajPoCijeni(void) {
	for (int i=0;i<brojClanova-1;++i) {
		int zamjena=0;
		for (int j=i+1;j<brojClanova;++j)
			if (hotel[i].Cijena()>hotel[j].Cijena()) {
				Hotel pomocni=hotel[i];
				hote[i]=hotel[j];
				hotel[j]=hotel[i];
				zamjena++;
			}
		if (zamjena==0) break;
	}
}