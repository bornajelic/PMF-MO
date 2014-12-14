/*
 * Zadatak 2:
 * KaĄzemo da su medusobno razliĄciti prirodni brojevi a i b prijateljski ako je zbroj svih djelitelja broja a, strogo manjih od a,
 * jednak broju b, a zbroj svih djelitelja broja b, strogo manjih od b, jednak broju a.
 * NapiĄsite program koji uĄcitava dva prirodna broja m i n, uz pretpostavku da je m < n, i ispisuje sve parove prijateljskih
 * brojeva (a, b), takve da je m ? a < b ? n. Svaki par treba ispisati toĄcno jednom.
 * Na primjer, ako je m = 100 i n = 300, onda program treba ispisati a = 220, b = 284, jer su to jedini prijateljski brojevi
 * izmedu 100 i 300. Brojevi a = 220 i b = 284 su prijateljski, jer su djelitelji broja a (strogo manji od njega): 1, 2, 4, 5, 10, 11,
 * 20, 22, 44, 55, 110 (suma im je 284), dok su djelitelji broja b (strogo manji od njega): 1, 2, 4, 71, 142 (njihova suma je 220).
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
	int m, n, a, b, zbroj_dj_a, zbroj_dj_b;
	scanf ("%d %d", &m, &n);
	for (a = m; a < n; ++a) {
		zbroj_dj_a = zbroj_djelitelja(a);
		for (b = 1; b < a; ++b) {
			zbroj_dj_b = zbroj_djelitelja(b);
			if (zbroj_dj_a == b && zbroj_dj_b == a) {
				printf("a = %d, b = %d\n", a, b);
			}
		}
	}
	
 }
