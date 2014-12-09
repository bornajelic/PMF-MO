#ifndef __SERVER_COMD_COUNT_H_
#define __SERVER_COMD_COUNT_H_

#include "h_server_command.h"

using namespace std;

class server_command_count : public server_command {
	public:
		server_command_count(
			data *studentsAndClassroomData,
			pthread_mutex_t *data_thread,
			pthread_mutex_t *output_thread
		);
		bool execute(int socket, char *message);
};

#endif
