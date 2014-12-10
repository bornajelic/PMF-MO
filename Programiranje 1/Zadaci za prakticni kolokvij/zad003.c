/* 
 * Zadatak 3:
 * Za broj n ∈ N, Eulerova funkcija ϕ(n) definira se kao broj prirodnih brojeva u skupu {1, . . . , n} koji su relativno prosti s n.
 * Napisati program koji ´ce uˇcitati prirodni broj n i ispisati vrijednost Eulerove funkcije od n
 */
 
 #include <stdio.h>
 
int main() {
	int n, i, relativno_prosti, j;
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		relativno_prosti = 1;
		for (j = 2; j <= i; ++j) {
			if (i%j == 0 && n%j == 0) {
				relativno_prosti = 0;
				break;
			}
		}
		if (relativno_prosti) {
			printf("%d\n", i);
		}
	}
	return 0;
}