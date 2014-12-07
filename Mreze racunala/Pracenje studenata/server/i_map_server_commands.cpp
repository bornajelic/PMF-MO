using namespace std;

#include "h_map_server_commands.h"

//defaultna komanda:

#include "h_server_command.h"

//koomande za mapiranje:

#include "h_server_command_update.h"
#include "h_server_command_count.h"
#include "h_server_command_locate.h"
#include "h_server_command_bye.h"
#include "h_server_command_error.h"

map_server_commands::map_server_commands(data *studentsAndClassroomData, pthread_mutex_t *dataLock, pthread_mutex_t *outputLock) {
	
	server_command	*update	= new server_command_update(studentsAndClassroomData, dataLock, outputLock);
	server_command	*locate	= new server_command_locate(studentsAndClassroomData, dataLock, outputLock);
	server_command	*count	= new server_command_count(studentsAndClassroomData, dataLock, outputLock);
	server_command	*bye	= new server_command_bye(studentsAndClassroomData, dataLock, outputLock);
	server_command	*error	= new server_command_error(studentsAndClassroomData, dataLock, outputLock);
	
	commands[UPDATE]	= update;
	commands[LOCATE]	= locate;
	commands[COUNT]		= count;
	commands[BYE]		= bye;
	commands[ERROR]		= error;
};

map<int, server_command*> map_server_commands::get_mapped_commands() {
	return commands;
};

map_server_commands::~map_server_commands() {
	map<int, server_command*>::iterator mi;
	for (mi = commands.begin(); mi != commands.end(); ++mi) {
		delete mi->second;
		commands.erase(mi);
	}
};
