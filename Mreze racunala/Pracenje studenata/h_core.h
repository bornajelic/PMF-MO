#ifndef __CORE_H_
#define __CORE_H_

#include "h_client_command.h"
#include "h_clientCommands.h"
#include "h_tokenizer.h"

#include <string>
#include <map>
#include <iostream>

using namespace std;

class core {
	private:
		clientCommands *commands;
	public:
		core(clientCommands *commands);
		void run(int socket);
};

#endif
