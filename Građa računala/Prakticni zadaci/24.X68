*-----------------------------------------------------------
* Program    : Zadatak 24 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Izračunajte najveći zajednički dijelitelj 16-bitnog
*		cijelog broja s adrese $6000 i 16-bitnog cijelog
*		broja s adrese $6010. Rezultat spremite na adresu
*		$6020 kao 16-bitni broj.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA

PRVI:	DS.W	8
DRUGI:	DS.W	8
REZ:	DS.W	1


	ORG	PROGRAM
START:				; first instruction of program

	MOVE.W	PRVI,D0
	MOVE.W	DRUGI,D1

LOOP:	MOVE.W	D1,D2
	CMP	D1,D0
	BMI	DALJE
	
	MOVE.W 	D0,D3
	MOVE.W	D1,D0
	MOVE.W	D3,D1
	
DALJE:	DIVU	D0,D1
	LSR.L	#8,D1
	LSR.L	#8,D1
	
	TST	D1
	BNE	LOOP	

	MOVE.W	D2,REZ
	
	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
