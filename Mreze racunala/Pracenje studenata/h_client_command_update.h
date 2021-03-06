#ifndef __CLIENT_COMD_UPDATE_H_
#define __CLIENT_COMD_UPDATE_H_

#include "h_client_command.h"
#include "h_tokenizer.h"

using namespace std;

class client_command_update : public client_command {
	public:
		client_command_update();
		string* getDescription();
		bool execute(int socket, tokenizer tokens);
};

#endif
