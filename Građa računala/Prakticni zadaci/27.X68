*-----------------------------------------------------------
* Program    : Zadatak 27 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Dodajte vrijednost 16 bitne varijable ITEM s adrese
*		$6000 u uzlazno sortiranu listu nenegativnih 16 bitnih
*		vrijednosti tako da se sortiranost očuva. Ako se broj
*		već nalazio u listi onda ga ne treba dodavati još
*		jednom. Adresa prvog elementa liste nalazi se na
*		adresi $6010, a prvi element liste sadrzi duljinu liste.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA
ITEM:	DS.W	1
PRVI:	EQU	$6010
	
	ORG	PROGRAM
START:				; first instruction of program
	MOVE.W	ITEM,D0
	MOVEA.L	PRVI,A0
	MOVE.W	(A0),D1
	MOVE.W	D1,D2
	ADDQ	#1,D1
	MOVE.W	D1,(A0)
	SUBQ	#2,D1
	ADD	D2,D2
	LEA	(A0,D2),A1
	LEA	2(A1),A2
	
LOOP1:	MOVE.W	(A1),D3
	LEA	-2(A1),A1
	CMP	D3,D0
	BGT	UBACI
	DBRA	D1,LOOP1
	
UBACI:	LEA	2(A2),A3
	LEA	4(A1),A1
UBACI1:	MOVE.W	(A2),D1
	LEA	-2(A2),A2
	MOVE.W	D1,(A3)
	LEA	-2(A3),A3
	CMPA	A1,A2
	BNE	UBACI1
	
	MOVE.W	(A2),D1
	LEA	-2(A2),A2
	MOVE.W	D1,(A3)
	LEA	-2(A3),A3

	MOVE.W	D0,(A1)

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
