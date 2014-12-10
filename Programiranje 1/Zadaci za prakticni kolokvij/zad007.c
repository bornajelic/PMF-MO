/*
 * Zadatak 7:
 * Za prirodni broj k, definiramo funkciju d(k) = broj svih djelitelja broja k, ukljuˇcivo i njega samog. Napiˇsite program koji
 * uˇcitava prirodni broj n i ispisuje tablicu vrijednosti funkcije d(k), za sve prirodne brojeve k manje ili jednake n. Na kraju,
 * treba ispisati za koji k se dostiˇze maksimum vrijednosti d(k). Ako takvih brojeva ima viˇse, treba ispisati najmanjeg.
 */

#include <stdio.h>

int broj_djelitelja(int n) {
	int broj_djelitelja = 1, i;
	for (i = 1; i < n/2; ++i) {
		if (n%i == 0) {
			broj_djelitelja++;
		}
	}
	return broj_djelitelja;
}

int main() {
	int n, k, max = 0, k_max = 0, d_k;
	scanf("%d", &n);
	for (k = 1; k <= n; ++k) {
		d_k = broj_djelitelja(k);
		if (d_k > max) {
			max = d_k;
			k_max = k;
		}
		printf("d(%d) = %d\n", k, d_k);
	}
	printf("Najveci broj djelitelja izmedu 1 i %d ima broj %d.\n", n, k_max);
	return 0;
}