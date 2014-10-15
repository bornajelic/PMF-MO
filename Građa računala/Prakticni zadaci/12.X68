*-----------------------------------------------------------
* Program    : Zadatak 12 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Odredite koji element u nizu 16 bitnih vrijednosti
*		ima najviše bitova jednakih 1. Duljina niza dana je
*		varijablom LENGTH s lokacije 6000 dok je početna
*		adresa niza dana 32 bitnom vrijednosti START s
*		lokacije 6002. Spremite element s najviše jedinica
*		na adresu 6006. Ako više elemenata ima jednak broj
*		jedinica onda spremite prvi takav na adresu 6006.
*-----------------------------------------------------------
DATA:		EQU	$6000
PROGRAM:	EQU	$6100
	
	ORG	DATA
LENGTH:		DS.W	1
POCETAK:	DS.L	1
RJESENJE:	DS.W	1
MASK:		EQU	$01

	ORG PROGRAM
START:
		MOVEA.L	POCETAK,A0
		MOVE.W	LENGTH, D0	*D0 duzina niza
		MOVEQ	#0,D1	*D1 najvise jedinica, D2 broj sa n.j.
		BEQ	LOOP

JEDINICA:
		MOVE.W	D3,D2
		MOVE.B	D6,D1
		BCC	DALJE

LOOP:				
		MOVE.W	(A0)+,D3	*D3 trenutni broj
		MOVE.W	D3,D4
		MOVEQ	#0,D6		*D6 broji jedinice u trenutnom
PETLJA:		
		MOVE.B	#MASK,D5
		AND.B	D4,D5
		ADD.B	D5,D6
		LSR.W	#1,D4
		BNE	PETLJA
		
		CMP.B	D6, D1
		BMI	JEDINICA
		
DALJE:		
		SUBQ	#1,D0
		BNE	LOOP
		
		MOVE.W D2,RJESENJE
		
		MOVE.B	#9,D0
		TRAP	#15
		END	START
		
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
