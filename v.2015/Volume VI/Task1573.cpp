// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

const int COLOR_LENGTH = 7;

int main() {
	int blue, yellow, red, k, result = 1;
	char c;
	cin >> blue >> red >> yellow >> k;
	for (int i = 0; i < k; i++) {
		cin >> c;
		cin.ignore(COLOR_LENGTH, '\n');
		switch(c) {
			case 'B':
				result *= blue;
				break;
			case 'Y':
				result *= yellow;
				break;
			case 'R':
				result *= red;
				break;
		}
	}
	cout << result;
}
