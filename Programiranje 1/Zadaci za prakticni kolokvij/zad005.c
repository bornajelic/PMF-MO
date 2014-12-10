/*
 * Zadatak 5:
 * Prirodni broj je savrˇsen, ako je jednak sumi svih svojih djelitelja, osim samog sebe. Na primjer, broj 6 je (najmanji) savrˇsen
 * broj, jer je 6 = 1 + 2 + 3. Napiˇsite program koji uˇcitava prirodni broj n i ispisuje sve savrˇsene brojeve manje ili jednake n.
 * Ako je takvih brojeva nema, treba ispisati odgovaraju´cu poruku.
 */

#include <stdio.h>

 int zbroj_djelitelja(int broj) {
	int zbroj = 0, i;
	for (i = 1; i <= broj/2; ++i) {
		if (broj%i == 0) {
			zbroj += i;
		}
	}
	return zbroj;
 }
 
int main() {
	int ima, n, i;
	scanf("%d", &n);
	ima = 0;
	for (i = 1; i <= n; ++i) {
		if (zbroj_djelitelja(i) == i) {
			printf("%d\n", i);
			ima = 1;
		}
	}
	if (!ima) {
		printf("Nema savrsenih brojeva manjih ili jednakih %d", n);
	}
	return 0;
}