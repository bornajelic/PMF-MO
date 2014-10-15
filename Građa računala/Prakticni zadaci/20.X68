*-----------------------------------------------------------
* Program    : Zadatak 20 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Konvertirajte vrijednost varijable CODE s adrese
*		$6000 iz sedmosegmentnog oblika (pogledati vježbe
*		za objašnjenje) u decimalan broj te spremite
*		rezultat na adresu $6010.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA
CODE:	DS.B	1
TABLICA: DC.B	$3F,$06,$5B,$4F,$66,$6D,$7D,$07,$7F,$6F

	ORG	PROGRAM
START:				; first instruction of program
	MOVEA.L	#TABLICA,A0
	MOVE.B	CODE,D1
	MOVEQ	#-1,D0

LOOP:	ADDQ	#1,D0
	MOVE.B	(A0)+,D2
	CMP.B	D1,D2
	BNE	LOOP
	
	MOVE.B	D0,$6010

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
