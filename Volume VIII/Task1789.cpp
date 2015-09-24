// Topic: games
// Subtopic: search
// Idea: go forward, then backward, changing distance parity with stop

#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;
	cout << (2 * n - 1) << '\n';
	for (int i = 1; i <= n; i++) {
		cout << i << ' ';
	}
	for(int i = n; i > 1; i--) {
		cout << i << ' ';
	}
}
