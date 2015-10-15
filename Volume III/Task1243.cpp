// Topic: arithmetic
// Subtopic: elementary
// Idea: Chinese remainder theorem

#include <iostream>

using namespace std;

const int MODS_COUNT = 6;
const int MODS[MODS_COUNT] = {1, 3, 2, 6, 4, 5};
const int MAX_DIGITS = 51;

int main() {
	char number[MAX_DIGITS];
	int result = 0, len;
	cin.getline(number, MAX_DIGITS);
	if(cin.eof()) {
		len = cin.gcount();
	} else {
		len = cin.gcount() - 1;
	}
	for (int i = len - 1, j = 0; i >= 0; i--) {
		result += MODS[j++] * (number[i] - '0');
		if (j == MODS_COUNT) {
			j = 0;
		}
	}
	cout << (result % (MODS_COUNT + 1));
}
