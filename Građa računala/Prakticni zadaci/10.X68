*-----------------------------------------------------------
* Program    : Zadatak 10 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Pronađite najmanji element u nizu unsigned bajtnih
*		vrijednosti. Duljina niza dana je varijablom LENGTH
*		s lokacije 6000 dok je početna adresa dana 32 bitnom
*		varijablom START s lokacije 6002. Spremite minimum
*		na adresu 6006.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM:	EQU	$6100

	ORG DATA
DUZINA:		DS.W	1
POCETAK:	DS.L	1
MINIMUM:	DS.B	1


	ORG PROGRAM
START:				; first instruction of program
	MOVE.W	DUZINA,D0
	MOVEA.L	POCETAK,A0
	MOVE.W	(A0),D2
LOOP:
	SUBQ	#1,D0
	BMI	GOTOVO

	MOVE.B	(A0)+,D1
	CMP.B	D2,D1
	BCC	LOOP
	MOVE.B	D1,D2
	BCC	LOOP


GOTOVO:	MOVE.B	D2,MINIMUM
	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
