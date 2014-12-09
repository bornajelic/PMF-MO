*-----------------------------------------------------------
* Program    : Zadatak 4 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Upišite na memorijsku lokaciju 6004 16 bitnu
*		vrijednost dobivenu kombinacijom najmanje
*		značajnih 4 bita bajtova s lokacije 6000-6003.
*		Bitove upisujte od najviše značajnih do
*		najmanje značajnih.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM:	EQU	$6100


	ORG DATA
MASK:	EQU	$000F
V1:	DS.B	1
V2:	DS.B	1
V3:	DS.B	1
V4:	DS.B	1
RJESENJE	DS.W	1
	
	ORG PROGRAM
START:				; first instruction of program

	MOVE.B	V1,D0
	AND.B	#MASK, D0
	LSL.W	#8, D0
	MOVE.B	V2, D0
	AND.B	#MASK, D0
	LSL.B	#4, D0
	LSR.W	#4, D0
	MOVE.B	D0, RJESENJE
	
	MOVE.B	V3, D0
	AND.B	#MASK, D0
	LSL.W	#8, D0
	MOVE.B	V4, D0
	AND.B	#MASK, D0
	LSL.B	#4, D0
	LSR.W	#4, D0
	MOVE.B	D0, RJESENJE+1
	
	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
