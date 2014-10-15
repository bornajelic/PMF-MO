*-----------------------------------------------------------
* Program    : Zadatak 25 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Pretvorite 32-bitni nenegativni broj s adrese $6000
*		u binarni ASCII prikaz te spremite rezutat na adresu
*		$6020. Početne nule zanemarite, a duljinu preostalog
*		ASCII niza zapišite na adresu $6010 kao 32-bitnu
*		vrijednost.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA

BROJ:	DS.L	1
NIZ:	EQU	$6010
PRIKAZ:	EQU	$6020


	ORG	PROGRAM
START:				; first instruction of program

	MOVE.L	BROJ,D0
	MOVE.L	#32,D1
	MOVEA.W	#PRIKAZ,A0
	
	
	
LOOP1:	LSL.L	#1,D0
	BCS	DALJE
	DBRA	D1,LOOP1
	
	
	
DALJE:	MOVE.L	D1,NIZ
	
	MOVE.B	#'1',(A0)+
	SUBQ	#2,D1
	
	
	
LOOP2:	MOVE.B	#'1',D2
	LSL.L	#1,D0
	BCS	NULA
	
	SUBQ	#1,D2
	
NULA:	MOVE.B	D2,(A0)+
	DBRA	D1,LOOP2
	
	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
