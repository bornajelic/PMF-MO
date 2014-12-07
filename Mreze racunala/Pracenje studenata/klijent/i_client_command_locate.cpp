#include "h_client_command_locate.h"

client_command_locate::client_command_locate() : client_command() {

};

bool client_command_locate::execute(int socket, tokenizer tokens) {
	
	
	//citanje jmbaga dvorane:
		
	if (!tokens.hasNext()) {
		cout << *getDescription() << endl;
		return false;
	}
	const char *jmbag_str = tokens.next().c_str();
	
	if (tokens.hasNext()) {
		cout << *getDescription() << endl;
		return false;
	}
	
	//provjera jmbaga:	
	
	if (!isNumber(jmbag_str)) {
		cout << "Pogresan unos! JMBAG se oznacava brojem!" << endl;
		return false;
	}
	if (strlen(jmbag_str) != JMBAG_LENGTH) {
		cout << "Pogresan unos! JMBAG je desetoznamenkast!" << endl;
		return false;
	}
	
	
	//pise poruku:
	
	char	message[JMBAG_LENGTH + 1];
	sprintf(message, "%s", jmbag_str);
	
	
	//salje poruku:

	cout << "Poslan zahtijev za lociranjem studenta " << jmbag_str << "!" << endl;
	send_message(socket, LOCATE, message);
	
	int	messageType,
		messageLength;
	char	*reply;
	
	if (
		receive_message(
			socket,
			&messageType,
			&messageLength,
			&reply
		)
		!= SUCESSFULL) {
		cout << "Greska u komunikaciji sa serverom!" << endl;
		return false;
	}
	
	if (
		(messageType != LOCATE && messageType != ERROR)
		|| messageLength == 0
		|| !isNumber(reply)
	) {
		cout << "Bug na serveru!" << endl;
		cout << "Server je poslao krivi odgovor!" << endl;
		return false;
	}
	
	if (
		messageType == ERROR
	) {
		cout << "Server javlja gresku u podacima, pokusajte ponovo!" << endl;
		return false;
	}
	
	int classroomID;
	sscanf(reply, "%d", &classroomID);
	
	cout << "Student " << jmbag_str;
	if (DATA_MIN_CLASSROOM_NO > classroomID) {
		cout  << " nije registriran";
	} else {
		cout << " se nalazi u dvorani " << reply;
	}
	cout << "." << endl;
	
	return false;
};

string* client_command_locate::getDescription() {
	return new string("Upotreba: locate <jmbag>");
};
