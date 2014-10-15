*-----------------------------------------------------------
* Program    : Zadatak 18 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Provjerite koji je, od dana 2 stringa, leksikografski
*		veći. Početna adresa stringova sadržana je u varijablama
*		START1 i START2 s adresa $6000 i $6004. Stringovi imaju
*		jednaku duljinu koja je sadržana u 16 bitnoj varijabli
*		LENGTH s adrese $6008. Ako je prvi string veći postavite
*		1 na adresu $6010. Ako su stringovi jednaki postavite 0
*		na adresu $6010. Inače, postavite -1 na adresu $6010.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA
START1:	DS.L	1
START2: DS.L	1
LENGTH:	DS.W	1
RJ:	DS.B	1

	ORG	PROGRAM
START:				; first instruction of program
	MOVEA.L	START1,A0
	MOVEA.L	START2,A1
	MOVE.B	#0,RJ
	MOVE.W	LENGTH,D0
	
	BRA	LOOP
	
PRVI:	MOVE.B	#1,RJ
	BRA	KRAJ
DRUGI:	MOVE.B	#-1,RJ
	BRA	KRAJ
	
LOOP:	MOVE.B	(A0)+,D1
	MOVE.B	(A1)+,D2
	
	CMP	D1,D2
	BHI	DRUGI
	BMI	PRVI


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
