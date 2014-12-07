#include "h_server_command_update.h"

server_command_update::server_command_update(
		data *studentsAndClassroomData,
		pthread_mutex_t *dataLock,
		pthread_mutex_t *outputLock
	) : server_command(
		studentsAndClassroomData,
		dataLock,
		outputLock) {

};
bool server_command_update::execute(int socket, char *message) {
	
	tokenizer *tokens = new tokenizer(string(message), ' ');
	
	string	jmbag		= getJMBAGstring(tokens, SC_NOT_LAST);
	string	dvoranaStr 	= getHallString(tokens, SC_LAST);
	
	if (jmbag.empty() || dvoranaStr.empty()) {
		send_message(socket, ERROR, "");
		return false;
	}
	

	int classroom = atoi(dvoranaStr.c_str());
	
	pthread_mutex_lock(outputLock);
	pthread_mutex_lock(dataLock);
	
	studentsAndClassroomData->assignClass(jmbag, classroom);
	pthread_mutex_unlock(dataLock);
	
	cout << socket << ":UPDATE (klijent br. " << socket << "): student "
		<< jmbag << " u dvorani " << classroom << "." << endl;
	pthread_mutex_unlock(outputLock);
	
	send_message(socket, UPDATE, "");
	
	return false;
};
