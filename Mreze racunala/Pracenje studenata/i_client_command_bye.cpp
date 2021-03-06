#include "h_client_command_bye.h"

client_command_bye::client_command_bye() : client_command() {

};

bool client_command_bye::execute(int socket, tokenizer tokens) {
	
	if (tokens.hasNext()) {
		cout << *getDescription() << endl;
		return false;
	}
	
	//salje poruku:
	cout << "Klijent se gasi!" << endl;
	send_message(socket, BYE, "");
	
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
	}
	
	if (
		messageType != BYE
		|| messageLength != 0
	) {
		cout << "Greska u komunikaciji sa serverom!" << endl;
		cout << "Server je poslao krivi odgovor!" << endl;
	}
	cout << "Dovidenja" << endl;
	return true;
};

string* client_command_bye::getDescription() {
	return new string("Upotreba: bye");
};
