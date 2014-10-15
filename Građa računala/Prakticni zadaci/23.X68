*-----------------------------------------------------------
* Program    : Zadatak 23 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Oduzmite dva BCD broja. Duljina (u bajtovima) dana
*		je varijablom LENGTH s adrese $6000. Najznačajniji
*		bajt prvog broja nalazi se na adresi $6010, a
*		najznačajniji bajt drugog broja nalazi se na adresi
*		$6020. Spremite sumu na adresu $6010.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA

LENGTH:	DS.B	16
PRVI:	DS.B	16
DRUGI:	DS.B	16


	ORG	PROGRAM
START:				; first instruction of program

	MOVE.B	LENGTH,D0
	MOVE	D0,A2
	LEA	PRVI(A2),A0
	LEA	DRUGI(A2),A1
	SUBQ	#1,D0
	
	MOVE	#0,CCR

LOOP:	SBCD	-(A1),-(A0)	
	DBRA	D0,LOOP
	


	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
