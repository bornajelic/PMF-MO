*-----------------------------------------------------------
* Program    : Zadatak 16 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Provjerite da li su tri niza ASCII znakova jednaka.
*		Početne adrese stringova dane su 32 bitnim varijablama
*		START1, START2, START3 s adresa $6000, $6004, $6008.
*		Prvi bajt svakog stringa označava duljinu tog stringa
*		u bajtovima. Ako su stringovi jednaki postavi varijablu
*		MATCH s adrese $600C na 0, inače postavi na -1.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA
START1	DS.L	1
START2	DS.L	1
START3	DS.L	1
MATCH	DS.B	1

	ORG	PROGRAM
START:				; first instruction of program
	
	MOVEA.L	START1,A0
	MOVEA.L	START2,A1
	MOVEA.L	START3,A2

	MOVE.B	#0,MATCH
	MOVE.B	(A0)+,D0
	MOVE.B	(A1)+,D1
	MOVE.B	(A2)+,D2
	
	CMP.B	D0,D1
	BNE	RAZL
	CMP.B	D0,D2
	BNE	RAZL
	
	BRA	LOOP
	
RAZL:	MOVE.B	#-1, MATCH
	BRA	KRAJ

LOOP:
	MOVE.B	(A0)+,D1
	MOVE.B	(A1)+,D2
	MOVE.B	(A2)+,D3
	
	CMP.B	D2,D1
	BNE	RAZL
	CMP.B	D3,D2
	BNE	RAZL
	
	SUBQ	#1,D0
	BNE	LOOP

KRAJ:	EQU	*
	
	
	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
