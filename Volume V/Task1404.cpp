// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

const char FIRST_SHIFT = 5;
const char LETTERS_COUNT = 26;
const char MAX_STRING_LENGTH = 101;

int main() {
	char str[MAX_STRING_LENGTH], prev, next;
	int len;
	cin.getline(str, MAX_STRING_LENGTH);
	if (cin.eof()) {
		len = cin.gcount();
	}	else {
		len = cin.gcount() - 1;
	}
	prev = str[0] - 'a';
	str[0] = (str[0] - 'a' + LETTERS_COUNT - FIRST_SHIFT) % LETTERS_COUNT + 'a';
	for (int i = 1; i < len; i++) {
		next = (str[i] - 'a' + LETTERS_COUNT - prev) % LETTERS_COUNT + 'a';
		prev = str[i] - 'a';
		str[i] = next;
	}
	cout.write(str, len);
}
