#ifndef __CLIENT_COMD_HELP_H_
#define __CLIENT_COMD_HELP_H_

#include "h_client_command.h"
#include "h_tokenizer.h"
#include "h_map_client_commands.h"

using namespace std;

class client_command_help : public client_command {
	private:
		map<string, client_command*> *commands;
		void printAll();
		client_command* getCommand(string keyWord);
		bool existsCommandFor(string keyWord);
	public:
		string* getDescription();
		client_command_help(map<string, client_command*> *commands);
		bool execute(int socket, tokenizer tokens);
		~client_command_help();
};

#endif
