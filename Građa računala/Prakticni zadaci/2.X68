*-----------------------------------------------------------
* Program    : Zadatak 2 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Oduzmite vrijednost 16 bitne varijable VALUE2
*		s lokacije 6002 od vrijednosti 16 bitne varijable
*		VALUE1 s lokacije 6000 i rezultat spremite u VALUE1.
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
	SUB.W	D1,D0
	MOVE.W	D0,VALUE1


	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
