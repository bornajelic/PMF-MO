/*
 * Zadatak 12:
 * Napiˇsite program koji uˇcitava prirodni broj n. Program treba ispisati najmanji prirodni broj m koji se na (barem) n razliˇcitih
 * naˇcina moˇze prikazati kao suma kvadrata dva prirodna broja, m = n
 * 2
 * 1 + n
 * 2
 * 2
 * , s tim da je n1 ≤ n2.
 */

#include <stdio.h>

int main() {
	int n, i, j, br, m = 0;
	scanf("%d", &n);
	br = 0;
	while (br < n) {
		++m;
		br = 0;
		for (i = 1; i < m; ++i) {
			for (j = 1; j <= i; ++j) {
				if (i*i + j*j == m) {
					br++;
				}
			}
		
		}
	}
	printf("%d", m);
	return 0;
}