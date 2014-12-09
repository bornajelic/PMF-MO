*-----------------------------------------------------------
* Program    : Zadatak 13 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Odredite duljinu ASCII poruke. Svi su znakovi 7-bitne
*		ASCII vrijednosti sa MSB=0. 32 bitna varijabla START
*		s adrese 6000 sadrži početnu adresu niza znakova među
*		kojima se nalazi poruka. Početni znak poruke je
*		$02 (STX), a krajnji $03 (ETX). Spremite duljinu
*		poruke (broj znakova između STX i ETX) na adresu 6004.
*-----------------------------------------------------------
DATA:	EQU	$6000
PROGRAM: EQU	$1000

	ORG DATA
START:	DS.L	1
RJ:	DS.B	1
PP:	EQU	02
KP:	EQU	03

	ORG PROGRAM
	
POCETAK:				; first instruction of program
	MOVEA.L	START,A0
	MOVE.B #-2,D0
	
PETLJA:	CMPI.B	#PP,(A0)+
	BEQ	PETLJA

LOOP:	ADDQ.B	#1,D0	
	CMPI.B	#KP,(A0)+
	BNE	LOOP
	
	MOVE.B	D0,RJ

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	POCETAK		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
