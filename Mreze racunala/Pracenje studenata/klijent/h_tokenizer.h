#ifndef __TOKENIZER_
#define __TOKENIZER_

#include <string>
#include <vector>

using namespace std;

class tokenizer {
	private:
		vector<string> separated;
		int v_current;
		int v_size;
	public:
		tokenizer(string to_tokenize, char separator);
		bool hasNext();
		string next();
		int size();
		int current();
};

#endif
