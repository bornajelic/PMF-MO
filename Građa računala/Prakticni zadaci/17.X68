*-----------------------------------------------------------
* Program    : Zadatak 17 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Neka su nam dana 2 stringa. Početna adresa stringova
*		sadržana je u varijablama START1 i START2 s adresa
*		$6000 i $6004. Početni bajt stringa označava njegovu
*		duljinu. Dodajte drugi string prvome i zapišite novi
*		string na adresu $6010. (Ne zaboravite i za novi string
*		postavati prvi bajt na njegovu duljinu).
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	%1000

	ORG	DATA
START1:	DS.L	1
START2:	DS.L	2
RJESENJE: EQU	$6010

	ORG	PROGRAM
START:				; first instruction of program
	MOVEA.L START1,A0
	MOVEA.L	START2,A1
	MOVEA.L	#RJESENJE,A2
	
	MOVE.B	(A0)+,D0
	MOVE.B	(A1)+,D1
	
	MOVE.B	D1,D2
	ADD.B	D0,D2
	
	MOVE.B	D2,(A2)+
	
LOOP1:	MOVE.B (A0)+,(A2)+
	SUBQ.B	#1,D0
	BNE	LOOP1

LOOP2:	MOVE.B (A1)+,(A2)+
	SUBQ.B	#1,D1
	BNE	LOOP2

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
