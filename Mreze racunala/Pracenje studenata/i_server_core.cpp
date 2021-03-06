#include "h_server_core.h"

using namespace std;

core::core(map<int, server_command*> commands, pthread_mutex_t *p_outputLock, threadPool *p_pool) : commands(commands) {
	outputLock = p_outputLock;
	pool = p_pool;
};

void core::run(int socket, int threadID) {
	bool stop = false;
	while (!stop) {
		
		int messageType, messageLength;
		char *message;
		if (
			receive_message(
				socket,
				&messageType,
				&messageLength,
				&message
			)
			== UNSUCESSFULL
		) {
			pthread_mutex_lock(outputLock);
			cout << "Greska u komunikaciji sa klijentom " << socket << endl;
			pthread_mutex_unlock(outputLock);
			
			break;
		}
		
		/*      //otkomentiarti ako se zeli vidjeti tocan izgled poruka:
		
		pthread_mutex_lock(outputLock);
		cout << socket << ": [" << messageType << " " << messageLength << "|" << message << "]"<< endl;
		pthread_mutex_unlock(outputLock);
		*/
		
		//trazi komandu:
		
		if (commands.count(messageType) == 0) {
			if (
				send_message(socket, ERROR, "")
				== UNSUCESSFULL
			) {
				pthread_mutex_lock(outputLock);
				cout << "Greska u komunikaciji sa klijentom " << socket << endl;
				pthread_mutex_unlock(outputLock);
			
				stop = true;
			}
		} else {
			stop = (commands[messageType])->execute(socket, message);
		}
	}
	pool->notifyFinished(threadID);
	close(socket);
};
