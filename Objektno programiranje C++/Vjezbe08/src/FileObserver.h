/*
 * FileObserver.h
 *
 *  Created on: 7. svi 2015.
 *      Author: Tomislav
 */

#ifndef SRC_FILEOBSERVER_H_
#define SRC_FILEOBSERVER_H_

#include <map>
#include <set>
#include <string>
#include <ctime>
#include <sys/stat.h>

class Observer {
public:
	virtual void update() = 0;
	virtual ~Observer() {
	}
};

class Subject {
private:
	std::set<Observer*> observers;
public:
	void attach(Observer * observer);
	void detach(Observer * observer);
	void notify();
	virtual ~Subject() {
	}
};

class IsFileModified {
private:
	std::string m_file_name;
	std::time_t get_last_modification_time();
protected:
	std::string get_file_name() {
		return m_file_name;
	}
public:
	IsFileModified(std::string file);
	bool is_modified_since(time_t last_read_time);
	virtual ~IsFileModified() {
	}
};

class Prices: public Subject, private IsFileModified {
private:
	std::map<std::string, double> price_list;
	time_t last_read_time;
	void read_file();
public:
	Prices(std::string file);
	std::map<std::string, double> get_state() {
		return price_list;
	}
	void set_state();
};

class DisplayInfo: public Observer {
private:
	Prices* m_subject;
public:
	DisplayInfo(Prices* subject);
	void update();
	~DisplayInfo();
};

#endif /* SRC_FILEOBSERVER_H_ */
