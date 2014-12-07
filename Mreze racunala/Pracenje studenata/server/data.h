#ifndef __DATA_H_
#define __DATA_H_

#include "pracenjeStudenataProtokol.h"

#include <string>
#include <map>

#ifndef __DATA_CONSTANTS__
#define __DATA_CONSTANTS__
#define DATA_DOESNT_EXIST 0
#define DATA_MIN_CLASSROOM_NO 1
#endif

using namespace std;

class data {
	private:
		map<string, int> studentsAndClassrooms;
	public:
		void assignClass(string jmbag, int classroom_id);
		int getClassroomIDfor(string jmbag);
		int getNoStudentsIn(int classroom_id);
};

#endif
