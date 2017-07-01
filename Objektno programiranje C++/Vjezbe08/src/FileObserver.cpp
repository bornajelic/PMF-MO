/*
 * FileObserver.cpp
 *
 *  Created on: 7. svi 2015.
 *      Author: Tomislav
 */

#include "FileObserver.h"
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include <fstream>

void check_null(Observer* observer) {
	if (observer == nullptr) {
		throw std::invalid_argument("Observer is null pointer.");
	}
}

void Subject::attach(Observer* observer) {
	check_null(observer);
	if (!observers.insert(observer).second) {
		throw std::invalid_argument("Observer already exists.");
	}
}
void Subject::detach(Observer* observer) {
	check_null(observer);
	observers.erase(observer);
}
void Subject::notify() {
	for (Observer* observer : observers) {
		observer->update();
	}
}

IsFileModified::IsFileModified(std::string file) :
		m_file_name(file) {
	if (access(m_file_name.c_str(), F_OK) == -1) {
		throw std::invalid_argument("File does not exist.");
	}
}
bool IsFileModified::is_modified_since(time_t last_read_time) {
	return std::difftime(get_last_modification_time(), last_read_time) > 0.0;
}

time_t IsFileModified::get_last_modification_time() {
	// C-kod za Unix platformu
	struct stat fileInfo;
	if (stat(m_file_name.c_str(), &fileInfo) != 0) {
		throw "stat error!";
	}
	return fileInfo.st_mtime;
}

Prices::Prices(std::string file) :
		IsFileModified(file), price_list(), last_read_time() {
	read_file();
}

void check_file_format_condition(bool check) {
	if (!check) {
		throw std::invalid_argument("Badly formated file.");
	}
}
void Prices::read_file() {
	time(&last_read_time);
	price_list.clear();
	std::ifstream file;
	file.open(get_file_name().c_str());
	std::string buffer, article;
	double price;
	std::string::size_type last_pos, curr_pos;
	const char SPACE = ' ';
	while (std::getline(file, buffer)) {
		if (buffer.find_first_not_of("\t\n ") == std::string::npos) {
			continue;
		}
		curr_pos = last_pos = 0;

		curr_pos = buffer.find(SPACE, 0);
		check_file_format_condition(curr_pos != std::string::npos);
		article = buffer.substr(last_pos, curr_pos);

		last_pos = curr_pos;
		curr_pos = buffer.find(SPACE, last_pos + 1);
		check_file_format_condition(curr_pos != std::string::npos);
		check_file_format_condition(
				buffer.substr(last_pos, curr_pos) != std::string(":"));

		last_pos = curr_pos;
		check_file_format_condition(
				buffer.find(SPACE, last_pos + 1) == std::string::npos);
		curr_pos = buffer.size();
		try {
			price = std::stod(buffer.substr(last_pos, curr_pos));
		} catch (std::exception &e) {
			check_file_format_condition(true);
		}
		price_list[article] = price;
	}
	file.close();
}

void Prices::set_state() {
	if (is_modified_since(last_read_time)) {
		read_file();
		notify();
	}
}

DisplayInfo::DisplayInfo(Prices* subject) :
		m_subject(subject) {
	if (m_subject == nullptr) {
		throw std::invalid_argument(
				"DisplayInfo class constructed with null pointer.");
	}
	m_subject->attach(this);
}

void DisplayInfo::update() {
	std::cout << "File updated! New values:" << std::endl;
	for (std::pair<std::string, double> article : m_subject->get_state()) {
		std::cout << article.first << " : " << article.second << std::endl;
	}
}

DisplayInfo::~DisplayInfo() {
	m_subject->detach(this);
}
