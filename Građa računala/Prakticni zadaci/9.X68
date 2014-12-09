*-----------------------------------------------------------
* Program    : Zadatak 9 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Odredite broj nula, pozitivnih (najznačajniji bit je 0)
*		je 0) i negativnih (najznačajniji bit je jednak 1)
*		vrijednosti u nizu 16 bitnih cijelih brojeva. Duljina
*		niza dana je varijablom LENGTH s lokacije 6000 i
*		početna adresa niza je sadržana u 32 bitnoj varijabli
*		START s lokacije 6002. Broj negativnih brojeva spremite
*		na adresu 6006, pozitivnih na adresu 6008 i broj nula
*		spremite na adresu 600A.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$6100

	ORG	DATA
	
LENGTH:	DS.W	1
POCETAK: DS.L	1
NEG:	DS.W	1
POZ:	DS.W	1
NUL:	DS.W	1



	ORG	PROGRAM
START:				; first instruction of program

	MOVEQ	#0,D0
	MOVEQ	#0,D1
	MOVEQ	#0,D2
	MOVEA.L	POCETAK,A0
	MOVE.W	LENGTH,D3
	BEQ	KRAJ
	
LOOP:	MOVE.W	(A0)+,D4
	BMI	NE
	BEQ	NU
	ADDQ	#1,D1
	SUBQ	#1,D3
	BNE	LOOP
	BEQ	KRAJ
	
NE:	ADDQ	#1,D2
	SUBQ	#1,D3
	BNE	LOOP
	BEQ	KRAJ

NU:	ADDQ	#1,D0
	SUBQ	#1,D3
	BNE	LOOP
	BEQ	KRAJ

KRAJ:	MOVE.W	D0,NUL
	MOVE.W	D1,POZ
	MOVE.W	D2,NEG

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
