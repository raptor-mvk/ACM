// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

int main() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	if (a > c) {
		cout << a;
	} else {
		cout << (a + (c - a) / (b + d) * b +
      ((c - a) % (b + d) > b ? b : (c - a) % (b + d)));
	}
}
