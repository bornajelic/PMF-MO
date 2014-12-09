/*
 * Moje rješenje zadatka sa prve godine.
 *
 * TEKST ZADATKA:
 *
 * Kemije Epruvetić, zli znanstvenik,
 * stvorio je novu vrstu virusa "Q01MUV"
 * koji živi 3 dana, te se razmnožava za
 * faktor 6 dnevno. Drugim riječima, od
 * jednog virusa dnevno nastane njih 6, a
 * uz njih ostane i on sam ako to nije
 * njegov 3. (posljednji) dan života. 
 *
 * Napišite program koji učitava prirodne
 * brojeve p i n, te ispisuje koliko virusa
 * će biti n-ti dan eksperimenta ako ih
 * nulti dan ima točno p i svi su novi
 * (tj. stari su nula dana i umrijet će
 * tek 3. dan). 
 */

#include <stdio.h>
long epruvetic(long virusa, long tri, long dva, long jedan, int n)
{
	if (n == 0) return virusa;
	return epruvetic(virusa*9 + virusa - tri, dva, jedan, virusa - tri - dva - jedan, n - 1);
}
int main(void)
{
	int n;
	long p,virusa;
	scanf("%ld, %d", &p, &n);
    printf ("%ld", epruvetic(p,0,0,0,n));
    return 0;
}