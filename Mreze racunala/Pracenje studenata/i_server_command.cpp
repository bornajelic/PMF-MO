#include "h_server_command.h"

using namespace std;

server_command::server_command(
		data *p_studentsAndClassroomData,
		pthread_mutex_t *p_dataLock,
		pthread_mutex_t *p_outputLock
	) {
	studentsAndClassroomData	= p_studentsAndClassroomData;
	dataLock			= p_dataLock;
	outputLock			= p_outputLock;
};
bool server_command::execute(int socket, char *message) {

	pthread_mutex_lock(outputLock);
	cout << "Osnovna komanda!" << endl << "Implementiraj ostale!" << endl;
	cout << "Primljena poruka je: " << message << endl;
	pthread_mutex_unlock(outputLock);
	
	return true;
};
bool server_command::isNumber(const char *s) {
	while (*s != '\0') {
	    	if (!isdigit(*s))
		return false;
		s++;
	}
	return true;
};
string server_command::getHallString(tokenizer *tokens, bool isLast) {
	
	if (!tokens->hasNext()) {
		return string("");
	}
	string hallStr = tokens->next();
	if (
		!isNumber(hallStr.c_str()) ||
		(isLast && tokens->hasNext())
	) {	
		cout <<  isNumber(hallStr.c_str()) << " " << isLast << " " << tokens->hasNext() << endl;
		return string("");
	}
	return hallStr;
};

string server_command::getJMBAGstring(tokenizer *tokens, bool isLast) {
	string jmbagStr = getHallString(tokens, isLast);
	return (jmbagStr == string("") || strlen(jmbagStr.c_str()) != JMBAG_LENGTH) ? string("") : jmbagStr;
};
