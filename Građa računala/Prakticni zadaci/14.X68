*-----------------------------------------------------------
* Program    : Zadatak 14 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Pronađite u danom stringu (nizu ASCII znakova) zadnji
*		ne "blank" znak. Početna adresa stringa sadržana je u
*		varijabli START s adrese $6000. Kraj stringa označen
*		je sa znakom CR ($0D). Spremite adresu zadnjeg ne
*		"blank" znaka na adresu $6004.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA
	
POC:	DS.L	1
RJ:	DS.L	1
CR:	EQU	$0D
BL:	EQU	' '

	ORG	PROGRAM
START:				; first instruction of program
	MOVEA.L	POC,A0
	MOVE.L	#0,RJ
	
	BRA	LOOP
	
BLANK:	CMPI.B	#0, -(A0)
	MOVE.L	A0,RJ
	CMPI.B	#0, (A0)+

	
LOOP:	CMPI.B	#CR, (A0)
	BEQ	KRAJ
	
	CMPI.B	#BL, (A0)+
	BNE	BLANK
	
	BRA	LOOP

KRAJ:	MOVE.W	D0,D1


	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
