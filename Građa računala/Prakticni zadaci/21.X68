*-----------------------------------------------------------
* Program    : Zadatak 21 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Konvertirajte vrijednost varijable NUMBER s adrese
*		$6000 u BCD oblik te spremite rezultat na adresu
*		$6010. Možete pretpostaviti da je vrijednost
*		prirodan broj manji od 10000.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA

NUMBER:	DS.W	8
RJ:	DS.W	1

	ORG	PROGRAM
START:				; first instruction of program
	MOVE.W	NUMBER,D0
	
	DIVU	#1000,D0
	MOVE.L	D0,D2
	
	LSR.L	#8,D0
	LSR.L	#8,D0
	LSL.W	#4,D2
	
	
	DIVU	#100,D0
	MOVE.L	D0,D1
	
	LSR.L	#8,D0
	LSR.L	#8,D0
	OR.W	D1,D2
	LSL.W	#4,D2
	
	DIVU	#10,D0
	MOVE.L	D0,D1
	
	LSR.L	#8,D0
	LSR.L	#8,D0
	OR.W	D1,D2
	LSL.W	#4,D2
	OR.W	D0,D2
	
	MOVE.W	D2,RJ
	
	

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
