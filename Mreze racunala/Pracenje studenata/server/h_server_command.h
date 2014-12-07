#ifndef __SERVER_COMMAND_H_
#define __SERVER_COMMAND_H_

#include <string>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>

#include "pracenjeStudenataProtokol.h"
#include "h_tokenizer.h"
#include "data.h"

/*
 * Interne naredbe za odredivanje da li je trazeni
 * parametar funkciji trebao biti zadnji.
 * Koristi se u funkcijama:
 * 	getJMBAGstring()
 * 	getHallString()
 */
#define 	SC_LAST		true
#define		SC_NOT_LAST	false

using namespace std;

class server_command {
	protected:
		data		*studentsAndClassroomData;
		pthread_mutex_t	*dataLock;
		pthread_mutex_t	*outputLock;
		bool isNumber(const char *s);
		string getJMBAGstring(tokenizer *tokens, bool isLast);
		string getHallString(tokenizer *tokens, bool isLast);
	public:
		server_command(
			data *studentsAndClassroomData,
			pthread_mutex_t *dataLock,
			pthread_mutex_t *outputLock);
		virtual bool execute(int socket, char *message);
};

#endif
