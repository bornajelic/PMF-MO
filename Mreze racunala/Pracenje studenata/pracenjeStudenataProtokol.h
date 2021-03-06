#ifndef __PRACENJESTUDENATAPROTOKOL_H_
#define __PRACENJESTUDENATAPROTOKOL_H_

/* 
 * Header: [ _OZNAKA_, _MESSAGE_LENGTH_ ]
 * 
 * Popis oznaka koristenih u headeru:
 * 	UPDATE	-	
 *		- Klijent: salje [LOCATE, length|-jmbag-room_id-] i ceka
 *		- Server: vraca [LOCATE, 0|] ili ERROR
 * 	LOCATE	-	
 *		- Klijent: salje [LOCATE, length|-jmbag-] i ceka
 *		- Server: vraca [LOCATE, length|-room_id-] ili ERROR
 * 	COUNT	-
 *		- Klijent: salje [COUNT, length|-room_id-] i ceka odgovor
 *		- Server: vraca [COUNT, length|-broj_studenata-] ili ERROR
 * 	BYE	-
 *		- Klijent: salje [BYE, 0|] i zatvara komunikaciju
 *		- Server: zatvara komunikaciju ili ERROR
 * 	ERROR	-
 *		- Klijent: /
 *		- Server: odgovara klijentu [ERROR, 0|]
 * 			 ako je klijent poslao pogresan zahtijev 
 */
#define	UPDATE		1
#define	LOCATE		2
#define COUNT		3
#define	BYE		4
#define	ERROR		0
/*
 * Velicina headera u byte-ovima
 */
#define HEADER_SIZE	8
/*
 * Duljina JMBAG-a
 */
#define	JMBAG_LENGTH	10
/*
/*
 * Funkcije za slanje i primanje poruka:
 * 	send_message();
 * 	recieve message();
 * 
 * Povratne varijable funkcija za slanje i primanje poruka:
 * 	SUCESSFULL	- slanje/primanje proslo uredu
 * 	UNSUCESSFULL	- greska prilikom slanja/primanja
 */
int send_message(int sock, int messageType, const char *message);
int receive_message(int sock, int *messageType, int *messageLength, char **message);
/*
 * Konstante za odgovore o uspjesnosti slanja/primanja poruka
 */
#define	SUCESSFULL	1
#define	UNSUCESSFULL	0
/*
 * Konstanta za rad sa podacima
 */
#ifndef __DATA_CONSTANTS__
#define __DATA_CONSTANTS__
#define DATA_DOESNT_EXIST 0
#define DATA_MIN_CLASSROOM_NO 1
#endif

#endif
