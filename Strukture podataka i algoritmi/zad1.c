#include <stdio.h>
#include <stdlib.h>

/*
 * Definicija tipa elementa sa kojim se barata u zadatku.
 */
typedef char elementtype;

/*
 * Definicija strukturu celije stoga. Sadrzi:
 * 		- element tipa elementtypež
 * 		- pokazivac na 'nizi' element
 */
typedef struct celltag {
	elementtype element;
	struct celltag *next;
} celltype;

/*
 * Stog je pokazivac na najvisociju celiju u strukturi:
 */
typedef celltype *Stack;

/*
 * Stvara prazan stog.
 */
void StMakeNull (Stack *Sp) {
	*Sp = NULL;
}

/*
 * Ako je stog prazan vraca 1, inace 0.
 */
int StEmpty (Stack S) {
	if (S == NULL)
		return 1;
	else
		return 0;
}

/*
 * Stavlja element tipa elementtype na vrh stoga.
 */
void StPush (elementtype x, Stack *Sp) {
	celltype *temp;
	temp = *Sp;
	*Sp = (celltype*) malloc(sizeof(celltype));
	(*Sp)->element = x;
	(*Sp)->next = temp;
}

/*
 * Brise najvisociji element sa vrha stoga.
 * Ako je stog prazan zatvara program uz status greske.
 */
void StPop (Stack *Sp) {
	celltype *temp;
	if (StEmpty(*Sp))
		exit(202); /* stog je prazan */
	else {
		temp = *Sp;
		*Sp = (*Sp)->next;
		free(temp);
	}
}

/*
 * Vraca element sa vrhsa stoga.
 * Ako je stog prazan zatvara program uz status greske.
 */
elementtype StTop (Stack S) {
	if (StEmpty(S))
		exit(202); /* stog je prazan */
	else
		return (S->element);
}




/* 
 * ZADATAK:
 * 
 * Implementirajte a.t.p. Stack pomoću pointera i napišite potprogram koji računa
 * vrijednost logičkog izraza zadanog u postfix obliku. Problem trebate riješiti pomoću
 * stoga.
 * Ulazni podaci: string koji predstavlja logički izraz u postfix obliku
 * Izlazni podaci: vrijednost unešenog izraza
 * Na primjer, za ulazne podatke:
 * 0101^0|&|
 * treba ispisati:
 * 1
 * Napomena: &=AND, |=OR, ^=XOR, -=NOT
 */


/*
 * Vraca 1 ako je c binarna znamenka, 0 ako nije. 
 */
int isBinary(elementtype c) {
	return (c == '0' || c == '1');
}

/*
 * Vraca 1 ako je c znak ekskluzivne disjunkcije, 0 ako nije. 
 */
int isXor(elementtype c) {
	return c == '^';
}

/*
 * Vraca 1 ako je c znak inkluzivne disjunkcije, 0 ako nije. 
 */
int isOr(elementtype c) {
	return c == '|';
}

/*
 * Vraca 1 ako je c znak konjukcije, 0 ako nije. 
 */
int isAnd(elementtype c) {
	return c == '&';
}

/*
 * Vraca 1 ako je c znak negacije, 0 ako nije. 
 */
int isNot(elementtype c) {
	return c == '-';
}


/*
 * Obavlja operaciju ekskluzivne disjunkcije i vraca rezultat.
 */
elementtype doXor(elementtype op1, elementtype op2) {
	//printf ("%c xor %c = %c\n", op1, op2, ((op1 - '0') ^ (op2 - '0')) + '0');
	return ((op1 - '0') ^ (op2 - '0')) + '0';
}

/*
 * Obavlja operaciju inkluzivne disjunkcije i vraca rezultat.
 */
elementtype doOr(elementtype op1, elementtype op2) {
	//printf ("%c or %c = %c\n", op1, op2, ((op1 - '0') | (op2 - '0')) + '0');
	return ((op1 - '0') | (op2 - '0')) + '0';
}

/*
 * Obavlja operaciju konjukcije i vraca rezultat.
 */
elementtype doAnd(elementtype op1, elementtype op2) {
	//printf ("%c and %c = %c\n", op1, op2, ((op1 - '0') & (op2 - '0')) + '0');
	return ((op1 - '0') & (op2 - '0')) + '0';
}

/*
 * Obavlja operaciju negacije i vraca rezultat.
 */
elementtype doNot(elementtype op) {
	//printf ("not %c = %c\n", op, (~(op - '0')) + '0');
	return (~(op - '0')) + '0';
}

/*
 * Vraca 1 ako je znak c binarni operator, 0 ako ne.
 */
int isBinaryOperator(elementtype c) {
	return (isAnd(c) || isOr(c) || isXor(c));
}

/*
 * Vraca 1 ako je znak c operator, 0 ako ne.
 */
int isOperator(elementtype c) {
	return (isBinaryOperator(c) || isNot(c));
}

/*
 * Prazni dobiveni stog S.
 */
void clearStack(Stack *S) {
	while (!StEmpty(*S)) {
		StPop(S);
	}
	free(*S);
}


/*
 * Zatvara program uz poruku o greski i brisanje stoga.
 */
void closeProgram(const char* message, Stack *S) {
	clearStack(S);
	printf(message);
	exit(-1);
}

/*
 * Deklaracija funkcije doOperation koja poziva specificnije
 * funkcije za obavljanje operacije za dobiveni operator.
 */
void doOperation(elementtype c, Stack *S);

/*
 * Funkcija vraca operand sa vrha stoga ako je operand na vrhu
 * stoga, inace racuna izraz dok na vrhu stoga ne dobije operand
 * koji ce vratiti pozivatelju.
 */
elementtype getOperand(Stack *S) {
	elementtype op;
	if (StEmpty(*S)) {
		closeProgram("Fali operand.", S);
	}
	while (isOperator(op = StTop(*S))) {
		if (StEmpty(*S)) {
			closeProgram("Fali operand.", S);
		}
		StPop(S);
		doOperation(op, S);
	}
	StPop(S);
	return op;
}

/*
 * Funkcija obavlja binarnu operaciju i stavlja rezultat
 * na vrh stoga.
 */
void doBinaryOperation(elementtype c, Stack *S) {
	elementtype op1, op2, res;
	
	op1 = getOperand(S);
	op2 = getOperand(S);
	
	if (isXor(c)) {
		res = doXor(op1, op2);
	} else if (isOr(c)) {
		res = doOr(op1, op2);
	} else if (isAnd(c)) {
		res = doAnd(op1, op2);
	} else {
		closeProgram("Binarna operacija nije implementirana!", S);
	}
	
	StPush(res, S);
}

/*
 * Funkcija obavlja unarnu operaciju i stavlja rezultat
 * na vrh stoga.
 */
void doUnaryOperation(elementtype c, Stack *S) {
	elementtype op, res;
	
	op = getOperand(S);
	
	if (isNot(c)) {
		res = doNot(op);
	} else {
		closeProgram("Unarna operacija nije implementirana!", S);
	}
	
	StPush(res, S);
}

/*
 * Implementacija vec opisane funkcije doOperation.
 */
void doOperation(elementtype c, Stack *S) {
	if (isBinaryOperator(c)) {
		doBinaryOperation(c, S);
	} else {
		doUnaryOperation(c, S);
	}
}


/*
 * Ucitava postfix logicki izraz sa tipkovnice i racuna njegovu vrijednost.
 */
char calculatePostFix() {
	elementtype c, result;
	Stack S;
	
	//stvara stog:
	StMakeNull(&S);
	//ucitava znakove dok nije unesen znak za novi red:
	while ((c = getchar())!='\n') {
		//za operatore stavlja poziva izvrednavanje izraza, operande stavlja
		//na vrh stoga, a inace zatvara program uz poruku o greski:
		if (isOperator(c)) {
			if (StEmpty(S)) {
				closeProgram("Ne moze se obavljati operacija bez operanada!", &S);
			}
			doOperation(c, &S);
		} else if (isBinary(c)) {
			StPush(c, &S);
		} else {
			closeProgram("Pogresan unos - nedozvoljeni znak! Unos iskljucivo mora biti binarna znamenka ili operator.", &S);
		}
	}
	
	//cita rezultat:
	result = StTop(S);
	StPop(&S);
	//ako je ostalo jos nerazrjesenih operanada dogodila se greska u unosu:
	if (!StEmpty(S)) {
		closeProgram("Oznacen je kraj unosa a nisu iskoristeni svi zadani operandi! Pokusajte ponovo uz dovoljno operatora.", &S);
	}
	clearStack(&S);
	return result;
}

/*
 * Glavni program
 */
int main() {
	printf("%c", calculatePostFix());
	return 0;
}