*-----------------------------------------------------------
* Program    : Zadatak 3 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Shiftajte vrijednost 16 bitne varijable VALUE1
*		sa lokacije 6000 udesno 3 bita te postavite
*		najznačajnija 3 bita varijable VALUE2 sa
*		lokacije 6006 na 0.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA
VALUE1	DS.W	1
VALUE2	DS.W	1

	ORG	PROGRAM
START:				; first instruction of program
	MOVE.W	VALUE1,D0
	MOVE.W	VALUE2,D1
	
	LSR.W	#3,D0
	LSL.W	#4,D1
	LSR.W	#4,D1
	
	MOVE.W	D0,VALUE1
	MOVE.W	D1,VALUE2


	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
