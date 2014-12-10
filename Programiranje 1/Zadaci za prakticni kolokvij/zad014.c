/*
 * Zadatak 14:
 * Napiˇsite program koji uˇcitava prirodni broj n ≥ 4. Program treba prona´ci prirodne brojeve m i k (oba strogo ve´ca od 1), takve
 * da je razlika n − m^k nenegativna i najmanja mogu´ca (najbolja aproksimacija broja n “odozdo”, netrivijalnom potencijom
 * prirodnog broja). Ispiˇsite n, m, k i dobivenu najmanju razliku. Ako ima viˇse rjeˇsenja za m i k, s istom najmanjom razlikom,
 * dovoljno je ispisati jedno rjeˇsenje (na primjer, ono s najmanjim m).
 * Primjer: za n = 17, izlazi da je 17 − 2^4
 * 4 = 17 − 4^2
 * 2 = 1, pa program treba ispisati brojeve 17, 2, 4, 1.
 */

#include <stdio.h>

int main() {
	int n, m = 1, k, min, best_m = 0, best_k = 0, best_min, zadnji = 1;
	scanf("%d", &n);
	best_min = n;
	while (m*m <= n) {
		k = 1;
		zadnji = m;
		while (zadnji*m <= n) {
			zadnji *= m;
			k++;
			if (m == 1) {
				break;
			}
		}
		if (n - zadnji < best_min && k != 1) {
			best_m = m;
			best_k = k;
			best_min = n - zadnji;
		}
		m++;
	}
	printf("%d %d %d %d", n, best_m, best_k, best_min);
	return 0;
}