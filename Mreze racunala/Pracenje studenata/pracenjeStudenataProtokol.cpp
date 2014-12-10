#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

#include "pracenjeStudenataProtokol.h"

int send_message(int sock, int messageType, const char *message) {
	
	//priprema header:
	
	int	message_length		= strlen(message);
	char	header[HEADER_SIZE + 1];
	
	sprintf(header, "%04d%04d", messageType, message_length);
	
	//salje header:
	
	int 	sent_total	= 0,
		last_sent	= 0;
		
	while (sent_total < HEADER_SIZE) {
		if (
			(last_sent = send(
				sock,
				header + sent_total,
				HEADER_SIZE - sent_total,
				0))
			== -1
		) {
			return UNSUCESSFULL;
		}
		sent_total += last_sent;
	}
	
	//salje poruku:
	
	sent_total	= 0;
	last_sent	= 0;
	
	while (sent_total < message_length) {
		if (
			(last_sent = send(
				sock,
				message + sent_total,
				message_length - sent_total,
				0))
			== -1
		) {
			return UNSUCESSFULL;
		}
		sent_total += last_sent;
	}
	return SUCESSFULL;
}

int receive_message(int sock, int *messageType, int *messageLength, char **message) {
	
	//prima header:

	int 	total_received		= 0,
		last_received		= 0;
		
	char	header[HEADER_SIZE + 1];
	
	while (total_received < HEADER_SIZE) {
		if (
			(last_received = recv(
				sock,
				header + total_received,
				HEADER_SIZE - total_received,
				0))
			== -1
		) {
			return UNSUCESSFULL;
		}
		total_received += last_received;
	}
	
	//cita i formatira podatke iz headera:
	
	sscanf(header, "%04d%04d", messageType, messageLength);

	//cita poruku:
	
	*message = (char *) malloc((*messageLength + 1)*sizeof(char));
	
	total_received		= 0,
	last_received		= 0;
	
	while (total_received < *messageLength) {
		if (
			(last_received = recv(
				sock,
				*message + total_received,
				*messageLength - total_received,
				0))
			== -1
		) {
			return UNSUCESSFULL;
		}
		total_received += last_received;
	}
	(*message)[*messageLength] = '\0';

	return SUCESSFULL;
}
