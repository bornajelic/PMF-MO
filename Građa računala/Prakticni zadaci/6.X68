*-----------------------------------------------------------
* Program    : Zadatak 6 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Izračunajte kvadrate 16 bitnih vrijednosti VALUE1,
*		VALUE2 s lokacija 6000, 6002 te spremite zbroj
*		kvadrata kao 32 bitnu vrijednost na lokaciju 6004.
*		Koristite signed aritmetiku.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA
VALUE1	DS.W	1
VALUE2	DS.W	1
RJ:	DS.L	1

	ORG	PROGRAM
START:				; first instruction of program
	MOVE.W	VALUE1,D0
	MOVE.W	VALUE2,D1
	
	MULS.W	D0,D0
	MULS.W	D1,D1
	ADD.W	D0,D1
	
	MOVE.L	D1,RJ


	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
