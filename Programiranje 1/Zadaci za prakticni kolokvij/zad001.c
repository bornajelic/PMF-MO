/*
 * Zadatak 1:
 * Za broj n ? N ka¡zemo da je obilan ako je strogo manji od zbroja
 * svojih djelitelja (izuzev¡si njega samog).
 * Na primjer, 12 < 1 + 2 + 3 + 4 + 6 = 16, pa
 * je 12 obilan broj, dok broj 16 > 1 + 2 + 4 + 8 = 15,
 * nije obilan broj.
 * Napisite program koji, za uneseni k ? N, ispisuje sve obilne
 * brojeve manje ili jednake k.
 */
 
 #include <stdio.h>
 
 int main() {
	int n, zbroj, br, i, j;
	scanf("%d", &n);
	for (i = 1; i <=n; ++i) {
		zbroj = 0;
		for (j = 1; j <= i/2; ++j) {
			if (i%j == 0) {
				zbroj += j;
			}
		}
		if (zbroj > i) {
			printf("%d\n", i);
		}
	}
	return 0;
 }