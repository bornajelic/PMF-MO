using namespace std;

#include "h_clientCommands.h"

clientCommands::clientCommands() {
	map_client_commands::fillCommands(&commands);
};

bool clientCommands::existsCommandFor(string keyWord) {
	return (commands.count(keyWord)!= 0);
};

void clientCommands::printAll() {
	cout << "Trenutno potoje naredbe:" << endl;
	map<string, client_command*>::iterator mi;
	for(
		mi = commands.begin();
		mi != commands.end();
		++mi
	) {
   		cout << "	" << mi->first << endl;
    	}
};

client_command* clientCommands::getCommand(string keyWord){
	return commands[keyWord];
};

clientCommands::~clientCommands() {
	map<string, client_command*>::iterator mi;
	for (mi = commands.begin(); mi != commands.end(); ++mi) {
		delete mi->second;
		commands.erase(mi);
	}
};
