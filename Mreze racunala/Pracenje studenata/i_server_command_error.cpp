#include "h_server_command_error.h"

server_command_error::server_command_error(
		data *studentsAndClassroomData,
		pthread_mutex_t *dataLock,
		pthread_mutex_t *outputLock
	) : server_command(
		studentsAndClassroomData,
		dataLock,
		outputLock) {

};
bool server_command_error::execute(int socket, char *message) {
	return false;
};
