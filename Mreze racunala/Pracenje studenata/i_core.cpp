#include "h_core.h"

using namespace std;

static const char prompt = '>';

core::core(clientCommands *commands) : commands(commands) {
};
void core::run(int socket) {
	int stop = 0;
	while (!stop) {
	
		//ucitava liniju:
		
		cout << prompt;
		string line;
		getline(cin, line);
		
		//trazi komandu:

		tokenizer tokens(line, ' ');
		string keyWord;
		try {
			keyWord = tokens.next();
		} catch (exception& e) {
			continue;
		}
		if (!commands->existsCommandFor(keyWord)) {
			cout << "Ne postoji dana naredba!" << endl;
			commands->printAll();
		} else {
			stop = commands->getCommand(keyWord)->execute(socket, tokens);
		}
	}
};
