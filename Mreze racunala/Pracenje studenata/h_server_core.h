#ifndef __SERVER_CORE_H_
#define __SERVER_CORE_H_

#include "h_server_command.h"
#include "data.h"
#include "pracenjeStudenataProtokol.h"
#include "h_threadPool.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <pthread.h>

#include <map>
#include <iostream>

using namespace std;

class core {
	private:
		map<int, server_command*> commands;
		pthread_mutex_t *outputLock;
		threadPool *pool;
	public:
		core(map<int, server_command*> commands, pthread_mutex_t *outputLock, threadPool *pool);
		void run(int socket, int threadID);
};

#endif
