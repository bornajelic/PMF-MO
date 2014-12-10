/*
 * Zadatak 13:
 * Napiˇsite program koji uˇcitava prirodni broj n ≥ 2 i provjerava je li broj n prost, koriste´ci slijede´ci (Wilsonov) teorem:
 * “Prirodni broj n je prost, ako i samo ako je ostatak pri dijeljenju (n − 1)! s n jednak −1”, odnosno, jednak n − 1 (u
 * standardnom sustavu ostataka modulo n). Program treba ispisati n i odgovaraju´cu poruku.
 * Uputa: Nemojte izravno raˇcunati (n − 1)! kao broj, ve´c mnoˇzenja radite samo s ostacima modulo n.
 * Primjer: neka je n = 5, a ostatke faktorijela raˇcunamo, na primjer, od 1 prema n − 1 = 4. Onda je, redom, 1 = 1 mod 5,
 * 2 · 1 = 2 mod 5, 3 · 2 = 1 mod 5, 4 · 1 = 4 mod 5. Zadnji ostatak je 4 = n − 1, pa je 5 prost broj.
 */

#include <stdio.h>

int main() {
	int n, i = 1, mod = 1;
	scanf("%d", &n);
	while (i < n && mod != 0) {
		mod = (i*mod)%n;
		++i;
	}
	if (mod == n - 1) {
		printf("%d je prost.", n);
	} else {
		printf("%d nije prost.", n);
	}
	return 0;
}