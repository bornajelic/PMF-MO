/*
 * Zadatak 4:
 * trokut sa stranicama ˇcije duljine su prirodni brojevi (na primjer, 3, 4, 5, ili 5, 12, 13). Napiˇsite
 * program koji uˇcitava prirodni broj n i nalazi sve Pitagorine trokute s hipotenuzom duljine n. Za svaki takav trokut treba
 * ispisati duljine sve tri stranice u uzlaznom poretku. Ako takvih trokuta nema, treba ispisati odgovaraju´cu poruku.
 */
 
#include <stdio.h>

int main() {
	int a, b, c;
	scanf("%d", &c);
	for (a = 1; a < c; ++a) {
		b = 1;
		while (
			b < a && b*b + a*a < c*c
		) {
			++b;
		}
		if (b*b + a*a == c*c) {
		printf ("%d %d %d\n", b, a, c);
		}
	}
	return 0;
}