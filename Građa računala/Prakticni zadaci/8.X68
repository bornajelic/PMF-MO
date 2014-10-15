*-----------------------------------------------------------
* Program    : Zadatak 8 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Izračunajte checksum niza 8 bitnih vrijednosti.
*		Duljina niza definirana je 16 bitnom varijablom
*		LENGTH s lokacije 6000. Početna adresa niza sadržana
*		je u 32 bitnoj varijabli START s lokacije 6002.
*		Spremite checksum na adresu 6006. Checksum je dan
*		operacijom isključivo ili među svim vrijednostima.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$6100

	ORG DATA
LENGTH:	DS.W	1
PRVA:	DS.L	1
REZULTAT: DS.B	1

	ORG PROGRAM
START:				; first instruction of program
	MOVEA.L	PRVA,A0
	MOVE.W	LENGTH,D1
	MOVE.B	(A0)+,REZULTAT
	SUBQ.B	#1,D1
	BEQ	KRAJ
	
LOOP:	MOVE.B	(A0)+,D0
	EOR.B	D0,REZULTAT
	SUBQ.B	#1,D1
	BNE	LOOP

KRAJ:
	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
