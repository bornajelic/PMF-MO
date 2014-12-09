*-----------------------------------------------------------
* Program    : Zadatak 1 za praktični kolokvij
* Written by : Tomislav Bukić
* Date       : 2013/14
* Description:
* 		Pomaknite sadržaj s memorijskih lokacija 6000-6006
* 		na lokacije 6800-6806. Sačuvajte redoslijed podataka.
*-----------------------------------------------------------
	ORG	$1000
START:				; first instruction of program
	MOVE.L	$6000,$6800
	MOVE.L	$6004,$6804

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
