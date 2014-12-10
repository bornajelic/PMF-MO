/* 
 * Zadatak 11:
 * Za prirodni broj n kaˇzemo da je obilan, ako je strogo manji od sume svih svojih djelitelja, osim njega samog. Napiˇsite
 * program koji uˇcitava prirodne brojeve k i m. Pretpostavljamo da je k ≤ m (ne treba provjeravati). Program treba ispisati
 * poˇcetak (prvi ˇclan) i duljinu (broj ˇclanova) najduljeg niza uzastopnih obilnih brojeva koje se nalaze izmedu brojeva k i m,
 * ukljuˇcivo i oba ta broja. Ako takvih nizova, iste najve´ce duljine, ima viˇse, onda treba ispisati najmanji poˇcetak. Ako takvog
 * niza nema, treba ispisati odgovaraju´cu poruku.
 * Primjer: za k = 6 i m = 15, jedini obilan broj imedu 6 i 15 je 12 (suma djelitelja je 16), pa program treba ispisati brojeve
 * 12 i 1.
 */

#include <stdio.h>

int s(int n) {
	int s = 0, i;
	for (i = 1; i <= n/2; ++i) {
		if (n%i == 0) {
			s += i;
		}
	}
	return s;
 }

int main() {
	int i, k, m, prvi, max_prvi = 0, max_niz = 0;
	scanf("%d %d", &k, &m);
	for (; k <= m; ++k) {
		prvi = k;
		i = prvi;
		while(i < m && s(i) == i++);
		if (i - (k + 1) > max_niz) {
			max_prvi = prvi;
			max_niz = i - (k + 1);
		}
	}
	if (max_niz == 0) {
		printf("Nema takvih nizova.");
	} else {
		printf("%d %d\n", max_prvi, max_niz);
	}
}