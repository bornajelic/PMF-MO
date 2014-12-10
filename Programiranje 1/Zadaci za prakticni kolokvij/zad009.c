/*
 * Zadatak 9:
 * Napiˇsite program koji uˇcitava prirodni broj n. Program treba ispisati koliko ima prirodnih brojeva, strogo ve´cih od 1, ˇciji
 * kvadrat dijeli broj n.
 * Primjer: broj n = 36 je djeljiv s 22
 * , 32
 * i 62
 * , pa program treba ispisati 3.
 */ 

#include <stdio.h>

int main() {
	int n, i, br = 0;
	scanf("%d", &n);
	for (i = 2; i < n/2; ++i) {
		if (n%(i*i) == 0) {
			br++;
		}
	}
	printf("%d\n", br);
}