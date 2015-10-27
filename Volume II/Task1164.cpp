// Topic: sort methods
// Subtopic: bucket sort
// Idea: calculate appearances of all letters in grid and in words,
//       the difference is the answer

#include "../Tools/Reader.h"

const int LETTERS_COUNT=26;
const int MAX_DATA_SIZE=11000;

int main() {
  FString::setMaxLength(MAX_DATA_SIZE);
	int m, n, p;
	FString str;
	Reader *r;
	char *data;
	char letters[LETTERS_COUNT];
	memset(letters, 0, LETTERS_COUNT);
	data = new char[MAX_DATA_SIZE];
	r = new Reader(cin, data, MAX_DATA_SIZE);
	r->fill();
	r->getNext<int>(&n, 'f', false);
	r->getNext<int>(&m, 'f', false);
	r->getNext<int>(&p, 'f', true);
	for (int i = 0; i < n; i++) {
		r->getNext(&str, &isEndl, 'f', true);
		for (int j = 0; j < m; j++) {
			letters[str[j] - 'A']++;
		}
	}
	for (int i = 0; i < p; i++) {
		r->getNext(&str, &isEndl, 'f', true);
		for (int j = 0, count = str.getLength(); j < count; j++) {
			letters[str[j] - 'A']--;
		}
	}
	for (int i = 0; i < LETTERS_COUNT; i++) {
		for (int j = 0; j < letters[i]; j++) {
			cout << (char)('A' + i);
		}
	}
}
