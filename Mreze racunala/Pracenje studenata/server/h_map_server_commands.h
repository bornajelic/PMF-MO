#ifndef __MAP_SERVER_COMMANDS_H_
#define __MAP_SERVER_COMMANDS_H_

#include "pracenjeStudenataProtokol.h"
#include "h_server_command.h"
#include "data.h"

#include <pthread.h>
#include <map>

using namespace std;

class map_server_commands {
	private:
		map<int, server_command*> commands;
	public:
		map_server_commands(data *studentsAndClassroomData, pthread_mutex_t *p_data_thread, pthread_mutex_t *p_output_thread);
		map<int, server_command*> get_mapped_commands();
		~map_server_commands();
};

#endif
