*-----------------------------------------------------------
* Program    : Zadatak 19 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Konvertirajte vrijednost varijable ADIGIT s adrese
*		$6000 iz ASCII znaka u odgovarajući heksadekadski
*		broj i spremite rezultat u varijablu HDIGIT s
*		adrese $6001.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA
ADIGIT	DS.B	1
HDIGIT	DS.B	1


	ORG	PROGRAM
START:				; first instruction of program
	MOVE.B	ADIGIT,D0
	
	CMP.B	#'A',D0
	BMI	DALJE
	
	SUB.B	#'A'-'0'-10,D0
	
DALJE:	SUB.B	#'0',D0
	
	MOVE.B	D0,HDIGIT


	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
