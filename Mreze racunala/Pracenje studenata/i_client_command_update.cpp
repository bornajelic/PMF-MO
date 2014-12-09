#include "h_client_command_update.h"

client_command_update::client_command_update() : client_command() {

};

bool client_command_update::execute(int socket, tokenizer tokens) {
	
	
	//citanje jmbaga i broja dvorane:
		
	if (!tokens.hasNext()) {
		cout << *getDescription() << endl;
		return false;
	}
	const char *jmbag_str = tokens.next().c_str();
	
	if (!tokens.hasNext()) {
		cout << *getDescription() << endl;
		return false;
	}
	const char *dvorana_str = tokens.next().c_str();
	if (tokens.hasNext()) {
		cout << *getDescription() << endl;
		return false;
	}
	
	//provjera jmbaga:	
	
	if (!isNumber(jmbag_str)) {
		cout << "Pogresan unos! JMBAG  se oznacava brojem!" << endl;
		return false;
	}
	if (strlen(jmbag_str) != JMBAG_LENGTH) {
		cout << "Pogresan unos! JMBAG je desetoznamenkast!" << endl;
		return false;
	}
	
	
	//provjera broja dvorane:
	
	if (!isNumber(dvorana_str)) {
		cout << "Pogresan unos! Dvorana se oznacava brojem!" << endl;
		return false;
	}
	
	
	//pise poruku:
	
	char	message[JMBAG_LENGTH + strlen(dvorana_str) + 1];
	sprintf(message, "%s %s", jmbag_str, dvorana_str);
	
	
	//salje poruku:

	cout << "Update podataka se salje!" << endl;
	send_message(socket, UPDATE, message);
	
	int	messageType,
		messageLength;
	char	*reply;
	
	//provjerava odgovor:
	
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
		(messageType != UPDATE && messageType != ERROR)
		|| messageLength != 0
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
	
	cout << "Update podataka uspjesno izvrsen!" << endl;
	return false;
};

string* client_command_update::getDescription() {
	return new string("Upotreba: update <jmbag broj_dvorane>");
};
