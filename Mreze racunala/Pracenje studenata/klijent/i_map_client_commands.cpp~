using namespace std;

#include "h_map_client_commands.h"

//defaultna komanda:

#include "h_client_command.h"

//koomande za mapiranje:

#include "h_client_command_bye.h"
#include "h_client_command_update.h"
#include "h_client_command_count.h"
#include "h_client_command_locate.h"
#include "h_client_command_help.h"

void map_client_commands::fillCommands(map<string, client_command*> *commands) {
	
	(*commands)["bye"]	= new client_command_bye();
	(*commands)["update"]	= new client_command_update();
	(*commands)["count"]	= new client_command_count();
	(*commands)["locate"]	= new client_command_locate();
	(*commands)["help"]	= new client_command_help(commands);
	(*commands)["?"]	= (*commands)["help"];
	
};
