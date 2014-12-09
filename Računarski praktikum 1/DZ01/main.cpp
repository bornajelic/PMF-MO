#include "hoteli.h"
#include <iostream>
using namespace std;
void ispisHotel(Hotel h){ cout << h.Ime() << " " << h.Grad() << " " << h.Cijena() << " " << h.BrojSlobodnihMjesta(); }
void ispisSkupHotela(SkupHotela hoteli) { for(int i=0; i<hoteli.BrojHotela(); i++) { ispisHotel(hoteli.ItiHotel(i)); cout << endl; } }
int main(void) {
SkupHotela test(Hotel("Hotel_1", "Zagreb", 500, 20)); test.Dodaj(Hotel("Hotel_2", "Zagreb", 300, 30)); test.Dodaj(Hotel("Hotel_3", "Zagreb", 250, 100)); test.Dodaj(Hotel("Hotel_4", "Split", 350, 200)); test.Dodaj(Hotel("Hotel_5", "Rijeka", 100, 150)); test.Dodaj(Hotel("Hotel_6", "Split", 120, 140 )); test.Dodaj(Hotel("Hotel_3", "Zagreb", 250, 100)); test.Dodaj(Hotel("Hotel_7", "Zagreb", 250, 25)); ispisSkupHotela(test);cout << test.Izbaci(Hotel("Hotel_3", "Zagreb", 250, 100)) << endl;ispisSkupHotela(test);test.SortirajPoCijeni(); ispisSkupHotela(test);cout << test.NajmanjaCijenaUGradu("Zagreb") << endl;ispisSkupHotela(test.NadjiHotele("Zagreb",300, 25));return 0;
}