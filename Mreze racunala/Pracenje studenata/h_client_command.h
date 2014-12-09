#ifndef __CLIENT_COMMAND_H_
#define __CLIENT_COMMAND_H_

#include <string>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>


#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "pracenjeStudenataProtokol.h"
#include "h_tokenizer.h"

using namespace std;

class client_command {
	protected:
		bool isNumber(const char *s);
	public:
		client_command();
		virtual string* getDescription();
		virtual bool execute(int socket, tokenizer tokens);
};

#endif
