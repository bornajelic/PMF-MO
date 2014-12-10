/* 
 * Zadatak 10:
 * Za prirodni broj n, definiramo funkciju s(n) kao sumu svih djelitelja od n, osim njega samog. Tako je s(1) = 0. Kaˇzemo
 * da je prirodni broj n “manjkav”, ako je ako je s(n) < n, “savrˇsen”, ako je s(n) = n, a “obilan”, ako je s(n) > n. Napiˇsite
 * program koji uˇcitava prirodni broj n i ispisuje broj manjkavih, broj savrˇsenih i broj obilnih brojeva manjih ili jednakih n.
 * Primjer: broj 8 je manjkav, jer je s(8) = 1 + 2 + 4 = 7 < 8, broj 6 je savrˇsen, jer je s(6) = 1 + 2 + 3 = 6, a broj 12 je obilan,
 * jer je s(12) = 1 + 2 + 3 + 4 + 6 = 16 > 12.
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
	int i, n, sav = 0, manj = 0, obi = 0, tren;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		tren = s(n);
		if (tren < i) {
			manj++;
		} else if (tren > i) {
			obi++;
		} else {
			sav++;
		}
	}
	printf("manjkavih: %d\nsavrsenih: %d\nobilnih: %d\n", manj, sav, obi);
}