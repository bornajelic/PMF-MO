#include "data.h"

void data::assignClass(string jmbag, int classroom_id) {
	if (classroom_id >= DATA_MIN_CLASSROOM_NO) {
		studentsAndClassrooms[jmbag] = classroom_id;
	}
};

int data::getClassroomIDfor(string jmbag) {
	return (studentsAndClassrooms.count(jmbag) != 0) ?
		studentsAndClassrooms[string(jmbag)] : DATA_DOESNT_EXIST;
};

int data::getNoStudentsIn(int classroom_id) {
	int no_students = 0;
	map<string, int>::iterator mi;
	for (mi = studentsAndClassrooms.begin(); mi != studentsAndClassrooms.end(); mi++) {
		if(mi->second == classroom_id) {
			++no_students;
		}
	}
	return no_students;
};
