/*
 * Zadatak 6:
 * Napiˇsite program koji uˇcitava prirodni broj n ≤ 10. Program prvo treba provjeriti je li n ≤ 10. Ako je, onda treba ispisati
 * najmanji prirodni broj sa svojstvom da pri dijeljenju s 2 daje ostatak 1, pri dijeljenju s 3 daje ostatak 2, pri dijeljenju s 4
 * daje ostatak 3, . . . , pri dijeljenju s n daje ostatak n − 1. Ako je n > 10, treba ispisati odgovaraju´cu poruku.
 * Na primjer, za n = 4, rezultat je 11.
 */

#include <stdio.h>

int main() {
	int n, nasao, i, br, trenutniTrazeni;
	scanf("%d", &n);
	if (n > 10) {
		printf("Uneseni broj %d je veci od 10! Upisi manji ili jednak.", n);
	} else {
		nasao = 0;
		br = n - 1;
		while (!nasao) {
			trenutniTrazeni = 1;
			for (int i = 2; i <= n; ++i) {
				if (br%i != i - 1) {
					trenutniTrazeni = 0;
					break;
				}
			}
			if (trenutniTrazeni) {
				nasao = 1;
				break;
			}
			br++;
		}
		printf("%d", br);
	}
	return 0;
}