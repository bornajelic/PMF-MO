*-----------------------------------------------------------
* Program    : Zadatak 15 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Zamijenite sve znakove poslije decimalne točke, u
*		danom stringu koji predstavalja decimalni broj, s
*		ASCII prazninama ("blank"). Početna adresa stringa
*		dana je varijablom START s adrese $6000. Duljina
*		stringa spremljena je u varijabli LENGTH s adrese
*		$6004. Možete pretpostaviti da se string sastoji
*		od isključivo znamenki '0',...,'9' ($30,...,$39)
*		i decimalne točke '.' ($2E).
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM EQU	$1000

	ORG DATA
	
POC:	DS.L	1
SIZE:	DS.W	1
TOC:	EQU	'.'
BL:	EQU	' '

	ORG	PROGRAM
START:				; first instruction of program
	
	MOVEA.L	POC,A0
	MOVE.W	SIZE,D0
	
LOOP:	SUBQ	#1,D0
	BEQ	KRAJ
	CMPI.B	#TOC,(A0)+
	BNE	LOOP
	
DEC:	MOVE.B	#BL, (A0)+
	SUBQ	#1,D0
	BNE	DEC

	
KRAJ:	EQU	*

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
