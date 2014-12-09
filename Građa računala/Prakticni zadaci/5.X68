*-----------------------------------------------------------
* Program    : Zadatak 5 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Memorijske lokacije 6002, 6004 i 6006
*		sadrže nenegativne cijele brojeve. Upišite
*		najmanjeg na lokaciju 6000.
*-----------------------------------------------------------
DATA	EQU	$6000
PROGRAM	EQU	$6100

	ORG	DATA
REZ:	DS.W	1
V1:	DS.W	1
V2:	DS.W	1
V3:	DS.W	1

	ORG	PROGRAM
START:				; first instruction of program
	MOVEM.W	V1, D0/D1
	CMP.W	D0, D1
	BHI	STORE1
	MOVE.W	D1, D0
STORE1:	MOVE.W	V3, D1
	CMP.W	D0,D1
	BHI	STORE2
	MOVE.W	D1,D0
STORE2:	MOVE.W	D0, REZ
	
	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
