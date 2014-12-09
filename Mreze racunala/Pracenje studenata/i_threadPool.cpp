#include <pthread.h>

#include "h_threadPool.h"

using namespace std;


threadPool::threadPool(int p_maxThreads, pthread_mutex_t *p_threadsLock, bool *p_canEnd) {
	maxThreads = p_maxThreads;
	threadsLock = p_threadsLock;
	canEnd = p_canEnd;
	for (int i = 0; i <= maxThreads; ++i) {
		freeID.push_back(i);
	}
};

bool threadPool::addThread(int threadID, pthread_t *thread) {
	pair<int, pthread_t*> toAdd(threadID, thread);
	bool registered = false;
	while(!registered) {
		pthread_mutex_lock(threadsLock);
		if (threads.size() < maxThreads) {
			for (
				list<pair<int, pthread_t*> >::iterator li = threads.begin();
				li != threads.end();
				++li
			) {
				if (li->first == threadID) {
					pthread_mutex_unlock(threadsLock);
					return false;
				}
			}
			threads.push_back(toAdd);
			registered = true;
		}
		pthread_mutex_unlock(threadsLock);
		if (!registered) {
			for (int i = 0; i < 10000; ++i);
		}
	}
	return true;
};

void threadPool::notifyFinished(int threadID) {
	pthread_mutex_lock(threadsLock);
	for (
		list<pair<int, pthread_t*> >::iterator li = threads.begin();
		li != threads.end();
		++li
	) {
		if (threadID == li->first) {
			pthread_join(*(li->second), NULL);
			freeID.push_back(li->first);
			threads.erase(li++);
		}
	}
	pthread_mutex_unlock(threadsLock);
};

void threadPool::programToEnd() {
	pthread_mutex_lock(threadsLock);
	for (
		list<pair<int, pthread_t*> >::iterator li = threads.begin();
		li != threads.end();
		++li
	) {
		pthread_join(*(li->second), NULL);
		freeID.push_back(li->first);
	}
	pthread_mutex_unlock(threadsLock);
	while(threads.size() != 0) {
	}
	*canEnd = true;
};

int threadPool::getFreeID() {
	pthread_mutex_lock(threadsLock);
	int id = freeID.front();
	freeID.pop_front();
	pthread_mutex_unlock(threadsLock);
	return id;
}
