// Topic: arithmetic
// Subtopic: elementary

#include <iostream>
#include "../Tools/Calculator.h"

using namespace std;

int main() {
	int y, n, m;
	bool found = false;
	cin >> n >> m >> y;
	for (int i = 0; i < m; i++) {
		if (Calculator::fastExpMod(i, n, m) == y) {
			cout << i << ' ';
			found = true;
		}
	}
	if (!found) {
		cout << -1;
	}
}
