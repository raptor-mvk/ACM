// Topic: arithmetic
// Subtopic: elementary

#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int n, res = 0, pos = 1, newPos;
	string s;
	cin >> n;
	getline(cin, s);
	for (int i = 0; i < n; i++) {
		getline(cin, s);
		switch (s[0]) {
			case 'A':
			case 'P':
			case 'O':
			case 'R':
				newPos = 1;
				break;
			case 'B':
			case 'M':
			case 'S':
				newPos = 2;
				break;
			default:
				newPos = 3;
		}
		res += abs(pos - newPos);
		pos = newPos;
	}
	cout << res;
}
