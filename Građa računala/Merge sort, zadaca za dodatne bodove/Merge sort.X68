*-----------------------------------------------------------
* Program    : Merge sort
* Written by : Tomislav Buki�
* Date       : 13.1.2014.
* Description: U memoriju na lokaciju $6000 unosi se vezana
*	lista koja se sastoji od podatka od 16 bajtova, te
*	adrese slijede�eg elementa od 32 bajta. Program listu
*	sortira uzlazno algoritmom Merge Sort.
*	Adresu gotove liste ponovo pi�e na $6000
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG		DATA
LISTA:	DS.L		1
NULL:	EQU		$FFFFFFFF
	ORG		PROGRAM
START:					; first instruction of program

	MOVEA.L		LISTA,A0
*	MOVE.L		$6008,A1
*	JSR		MERGE
	JSR		COUNT
	JSR		MSORT
	MOVE.L		A0,LISTA

	MOVE.B		#9,D0
	TRAP		#15		; halt simulator

* Variables and Strings


*POTPROGRAM
*Spaja uzlazno dvije uzlazno sortirane liste
*Dobiva:		A0,A1
*Vra�a:			A0
*Koristi:	
*	2 pomo�ne liste:
*		A4->	|D2|A2|	 	A2->next	"GORNJA"
*		A3->	|D1|A1| 	A2->next	"DONJA"
*	Listu rje�enja:
*		A0-> first...list...->A5->last
MERGE:	MOVEM.L		D1-D2/A2-A5,-(A7)
	
	
	*PROVJERI JELI PRAZNA (JEDNA OD) LISTA:
	CMPA		#NULL,A0
	BEQ		PRVIP
	CMPA		#NULL,A1
	BEQ		GOTOVO
	
	
	*SLO�I POMO�NE LISTE:
	LEA		(A0),A2		*A0->prvi element liste rje�enja
	LEA		(A0),A4		*trenutni elementi A4,A3
	LEA		(A1),A3
	MOVE.W		(A1)+,D1	
	MOVE.W		(A2)+,D2 	*trenutne vrijednosti D1,D2
	MOVEA.L		(A1),A1		*idu�i elementi	A1,A2
	MOVEA.L		(A2),A2



	*SLO�I ZAGLAVLJE RJE�ENJA:
	CMP.W		D2,D1		*gleda jesu prva 2 u pravom redoslijedu
	BHI		DALJE
	
	LEA		(A3),A0 	*sredi pokaziva�e po�etak na liste rje�enja	
	JSR		SWA3A4		*zamijenjeni pokaziva�i na po�etne liste, prva je manja
	JSR		SWD1D2		*nakon pokaziva�a i data registri poredani
	
DALJE:	LEA		(A0),A5		*A5->zadnji element

	CMPA		#NULL,A2	*[ubacio zbog bug-a 1, kontrolira da ne u�ita NULLL]
	BEQ		GTV1
	
	JSR		NXTA4		*A4 i A3 sad pokazuju na idu�a dva elementa liste



	*PUNI RJE�ENJE:
LOOP:	CMPA		#NULL,	A3
	BEQ		GOTOVO
	CMPA		#NULL,	A4	*NIJE DOBRO!
	BEQ		GTV1
	
	
		
	CMP		D2,D1		*sla�e �lanove liste
	BHI		DALJE1	
	
	JSR		SWD1D2		*mijenja D registre u pravi red
	JSR		SWA3A4		*mijenja A registre u pravi red
	
DALJE1:	JSR		UBCA		*ubacuje gornju listu u rje�enje

	CMPA		#NULL,A2	*[ubacio zbog bug-a 2, kontrolira da ne u�ita NULLL]
	BEQ		GTV1
	
	JSR		NXTA4		*gornja lista ide dalje
	BRA		LOOP


	BRA 		GOTOVO
	
PRVIP:	LEA		(A3),A0
	BRA		GOTOVO	
	
GTV1:	LEA		2(A5),A5
	MOVE.L		A3,(A5)	

GOTOVO:	MOVEM.L		(A7)+,D1-D2/A2-A5
	RTS
	
	
	
*POTPROGRAM:	
*prima registre D1,D2 te ih mijenja:

SWD1D2:	MOVE.L		D3,-(A7)

	MOVE.W		D1,D3
	MOVE.W		D2,D1
	MOVE.W		D3,D2
	
	MOVE.L		(A7)+,D3
	RTS



*POTPROGRAM:	
*prima A4,A2 i A3,A1 te ih mijenja

SWA3A4:	MOVE.L		A0,-(A7)

	LEA		(A1),A0
	LEA		(A2),A1
	LEA		(A0),A2
	
	LEA		(A3),A0
	LEA		(A4),A3
	LEA		(A0),A4
	
	MOVE.L		(A7)+,A0
	RTS
	
	
	
*POTPROGRAM:
*prima A4,D2,A2 i postavlja na idu�i element liste

NXTA4:	LEA		(A2),A4
	MOVE.W		(A2)+,D2
	MOVEA.L		(A2),A2
	
	RTS
	
	
	
*POTPROGRAM:
*prima A4 i ubacuje ga u A0
*Koristi:
	
UBCA:	LEA		2(A5),A5
	MOVE.L		A4,(A5)
	LEA		(A4),A5
	
	RTS
	

	
*POTPROGRAM:
*broji elemente liste
*Dobiva: A0
*Vra�a:	D0 (broj elemenata zadane liste)

COUNT:	MOVE.L		A1,-(A7)
	LEA		(A0),A1
	CLR		D0
	BRA		P1E
PTLJ:	ADDQ		#1,D0
	LEA		2(A1),A1
	MOVEA.L		(A1),A1
P1E:	CMP		#NULL,A1
	BNE		PTLJ

	MOVE.L		(A7)+,A1
	RTS
	
	
	
*POTPROGRAM:
*sortira listu uzlazno Merge Sort algoritmom
*Dobiva:
*	A0 (pokaziva� na po�etak vezane liste)
*	D0 (broj elemenata vezane liste)

MSORT:	MOVEM.L		D1-D2/A1-A2,-(A7)
	
	
	*Postavlja D1 kao broj elemenata desne (du�e) podliste, D2 broj elemenata lijeve
	CLR		D2
	MOVE.L		D0,D1
	DIVU		#2,D1
	MOVE.W		D1,D2
	LSR.L		#8,D1
	LSR.L		#8,D1
	ADD.L		D2,D1

	JSR		SPLIT		*vra�a A1 (D1 komada), A2 (D2 komada)
		
	
	*Postavlja registre i sortira prvu podlistu:
	MOVE.W		D1,D0
	LEA		(A1),A0
	CMP		#2,D0
	BMI		MS1
	JSR		MSORT		*dobiva A0,D0, vra�a A0
	
	*Postavlja registre i sortira drugu podlistu:
MS1:	MOVE.W		D2,D0
	LEA		(A0),A1
	LEA		(A2),A0
	CMP		#2,D0
	BMI		MS2
	JSR		MSORT		*dobiva A0,D0, vra�a A0
	BRA		MS3

MS2:	LEA		(A2),A0
	
MS3:	JSR		MERGE		*dobiva A0,A1, vra�a A0
	
	MOVEM.L		(A7)+,D1-D2/A1-A2
	RTS
		

*POTPROGRAM:
*daje prvih D1 elemenata liste A0 u A1, i ostalih D2 u A2

SPLIT:	MOVE.L		D1,-(A7)
	LEA		(A0),A2
	SUBQ		#1,D1
	
PPTT1:	LEA		2(A2),A1
	MOVEA.L		(A1),A2
	DBRA		D1,PPTT1
	MOVE.L		#NULL,(A1)
	LEA		(A0),A1

	MOVE.L		(A7)+,D1
	RTS

	END		START		; last line of source


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
