#include "h_tokenizer.h"

using namespace std;

tokenizer::tokenizer(string to_tokenize, char separator) {

	int cursor_current = 0;
	while (cursor_current < to_tokenize.length()) {
		int cursor_first = cursor_current;
		while (
			to_tokenize[cursor_current] != separator
			&& cursor_current < to_tokenize.length()
		) {
			cursor_current++;
		}
		if (cursor_first != cursor_current) {
			separated.push_back(
				to_tokenize.substr(
					cursor_first,
					cursor_current - cursor_first
				)
			);
		}
		while (to_tokenize[cursor_current] == separator) {
			cursor_current++;
		}
	}
	v_current = 0;
	v_size = separated.size();
};
bool tokenizer::hasNext() {
	return v_current < v_size;
};
string tokenizer::next() {
	return hasNext() ? separated[v_current++] : NULL;
};
int tokenizer::size() {
	return v_size;
};
int tokenizer::current() {
	return v_current;
};
