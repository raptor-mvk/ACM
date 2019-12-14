// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

const int SATISFIED = 10;
const int HUNGRY = 2;
const int MAX_LENGTH = 10;

int main() {
	int n, hungry, satisfied, cur;
	char c;
	cin >> n;
	hungry = HUNGRY;
	satisfied = SATISFIED;
	for (int i = 0; i < n; i++) {
		cin >> cur;
		cin.ignore(1, ' ');
		cin >> c;
		cin.ignore(MAX_LENGTH, '\n');
		if ((c == 'h' && cur >= SATISFIED) || (c == 's' && cur <= HUNGRY)) {
			hungry = satisfied;
			break;
		}
		if (c == 'h' && hungry < cur) {
			hungry = cur;
		}
		if (c == 's' && satisfied > cur) {
			satisfied = cur;
		}
	}
	if (hungry >= satisfied) {
		cout << "Inconsistent\n";
	} else {
		cout << satisfied;
	}
}
