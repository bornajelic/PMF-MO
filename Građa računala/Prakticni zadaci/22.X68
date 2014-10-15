*-----------------------------------------------------------
* Program    : Zadatak 22 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		OOduzmite dva 56-bitna broja. Prvi se broj nalazi na
*		adresama 6000-6006, a drugi na adresama 6010-6016.
*		Spremite sumu na adrese 6000-6006. Možete
*		pretpostaviti da je prvi broj veći ili jednak drugom.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG	DATA

NUM1:	DS.B	16
NUM2:	DS.B	7

	ORG	PROGRAM
START:				; first instruction of program
	MOVEA.L	#NUM1+7,A0
	MOVEA.L #NUM2+7,A1
	MOVE	#0,CCR
	SUBX.B	-(A1),-(A0)
	SUBX.B	-(A1),-(A0)
	SUBX.B	-(A1),-(A0)
	SUBX.B	-(A1),-(A0)
	SUBX.B	-(A1),-(A0)
	SUBX.B	-(A1),-(A0)
	SUBX.B	-(A1),-(A0)
	
LOOP	
	
	

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
