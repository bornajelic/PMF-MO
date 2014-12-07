#include "h_client_command_help.h"

client_command_help::client_command_help(map<string, client_command*> *p_commands) : client_command() {
	commands = p_commands;
};

bool client_command_help::execute(int socket, tokenizer tokens) {
	
	//citanje jmbaga i broja dvorane:
		
	if (!tokens.hasNext()) {
		cout << *getDescription() << endl;
		printAll();
		return false;
	}
	
	string keyWord = tokens.next();
	if (tokens.hasNext()) {
		cout << *getDescription() << endl;
		return false;
	}
	if (existsCommandFor(keyWord)) {
		cout << *(getCommand(keyWord)->getDescription()) << endl;
	} else {
		printAll();
	}
	return false;
};
string* client_command_help::getDescription() {
	return new string("Upotreba:\n\thelp <ime_naredbe>\n\t? <ime_naredbe>");
}

void client_command_help::printAll() {
	cout << "Trenutno potoje naredbe:" << endl;
	map<string, client_command*>::iterator mi;
	for(
		mi = commands->begin();
		mi != commands->end();
		++mi
	) {
		if (mi->second != this) {
   			cout << "	" << mi->first << endl;
   		}
    	}
};

client_command* client_command_help::getCommand(string keyWord){
	return (*commands)[keyWord];
};
bool client_command_help::existsCommandFor(string keyWord) {
	return (commands->count(keyWord)!= 0);
};
client_command_help::~client_command_help() {
	map<string, client_command*>::iterator mi;
	for (mi = commands->begin(); mi != commands->end(); ++mi) {
		delete mi->second;
		commands->erase(mi);
	}
};
