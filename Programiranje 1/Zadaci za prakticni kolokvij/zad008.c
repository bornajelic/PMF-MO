/*
 * Zadatak 8:
 * Napiˇsite program koji uˇcitava prirodni broj n i ispisuje najve´ci prirodni broj m, manji ili jednak n, sa sljede´cim svojstvima:
 * broj m je potpun kvadrat nekog prirodnog broja, zadnja znamenka (jedinica) u dekadskom zapisu broja m je 9, pri dijeljenju
 * broja m s 3 dobivamo ostatak 1. Ako takvog broja m nema, treba ispisati odgovaraju´cu poruku.
 * Na primjer, za n = 200, rezultat je m = 169 = 132
 * Najmanji broj s traˇzenim svojstvima je 49 = 72 = 16 · 3 + 1.
 */

#include <stdio.h>

int jePotpuniKvadrat(int n) {
	int i = 0;
	while (i*i < n) {
		++i;
	}
	if (i*i == n) {
		return 1;
	}
	return 0;
}

int main() {
	int n;
	scanf("%d", &n);
	for (; n > 9; --n) {
		if(n%3 == 1 && n%10 == 9 && jePotpuniKvadrat(n) == 1) {
			printf("%d\n", n);
			break;
		}
	}
	if (n <= 9) {
	
	}
	return 0;
}