*-----------------------------------------------------------
* Program    : Zadatak 7 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Izračunajte faktorijelu 8 bitne varijable VALUE
*		s lokacije 6010 pomoću tablice faktorijela FTABLE
*		s lokacija 6000-600F. Spremite rezultat u 16 bitnu
*		varijablu RESULT na lokaciju 6012. Pretpostavite
*		da je VALUE vrijednost između 0 i 7.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$6100

	ORG	DATA
FTABLE: DS.W	8	
VALUE:	DS.B	1
RESULT: DS.W	1

	ORG	PROGRAM
START:				; first instruction of program
	MOVE.B	VALUE,D0
	MOVEA.W	#$6000,A0
	
LOOP:	MOVE.W	(A0)+,D1
	SUBQ.B	#1,D0
	BPL	LOOP
	
GOTOVO:	MOVE.W	D1, RESULT

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
