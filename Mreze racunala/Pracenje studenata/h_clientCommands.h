#ifndef __CLIENTCOMNDS_H_
#define __CLIENTCOMNDS_H_

#include "h_client_command.h"
#include "h_map_client_commands.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

class clientCommands {
	private:
		map<string, client_command*> commands;
	public:
		clientCommands();
		void printAll();
		bool existsCommandFor(string keyWord);
		client_command* getCommand(string keyWord);
		~clientCommands();
};

#endif



