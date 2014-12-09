*-----------------------------------------------------------
* Program    : Zadatak 11 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Odrediti broj bitova koji su jednaki 1 u 16 bitnoj
*		varijabli NUM s lokacije 6000 i spremite rezutat
*		na adresu 6002.
*-----------------------------------------------------------

DATA:	EQU	$6000
PROGRAM: EQU	$6010
	ORG	DATA
NUM:	DS.W	1
RJ:	DS.B	1
	DS.B	1
MASK	EQU	$01
	
	ORG	PROGRAM
START:				; first instruction of program
	MOVEQ	#0,D0
	MOVE.W	NUM,D1
LOOP:
	MOVE.B	#MASK,D2
	AND.B	D1,D2
	ADD.B	D2,D0
	LSR.W	#1,D1
	BNE	LOOP
	
	MOVE.B	D0,RJ

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
