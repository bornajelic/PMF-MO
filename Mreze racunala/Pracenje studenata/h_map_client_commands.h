#ifndef __MAP_CLIENT_COMMANDS_H_
#define __MAP_CLIENT_COMMANDS_H_

#include "h_client_command.h"
#include <map>
#include <string>

using namespace std;

class map_client_commands {
	public:
		static void fillCommands(map<string, client_command*> *commands);
};

#endif
