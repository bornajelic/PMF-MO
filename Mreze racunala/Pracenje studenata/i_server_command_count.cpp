#include "h_server_command_count.h"

server_command_count::server_command_count(
		data *studentsAndClassroomData,
		pthread_mutex_t *dataLock,
		pthread_mutex_t *outputLock
	) : server_command(
		studentsAndClassroomData,
		dataLock,
		outputLock) {

};
bool server_command_count::execute(int socket, char *message) {
	
	tokenizer *tokens = new tokenizer(string(message), ' ');
	
	string	dvoranaStr 	= getHallString(tokens, SC_LAST);
	
	if (dvoranaStr.empty()) {
		send_message(socket, ERROR, "");
		return false;
	}
	

	int classroom_id = atoi(dvoranaStr.c_str());
	
	pthread_mutex_lock(outputLock);
	pthread_mutex_lock(dataLock);
	
	int no_students = studentsAndClassroomData->getNoStudentsIn(classroom_id);
	pthread_mutex_unlock(dataLock);
	
	
	cout << socket << ":COUNT (klijent br. " << socket << "): student (@" << classroom_id << ") = " << no_students << "." << endl;
	pthread_mutex_unlock(outputLock);
	
	int toAllocate = (no_students > 0) ? ((int) floor(log10(no_students)) + 2) : 2;
	char to_send[toAllocate];
	sprintf(to_send, "%d", no_students);
	send_message(socket, COUNT, to_send);
	
	return false;
};
