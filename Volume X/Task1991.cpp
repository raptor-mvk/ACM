// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

int main() {
	int n, k, b = 0, d = 0, a;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> a;
		if (a > k) {
      b += a - k;
		} else {
		  d += k - a;
		}
	}
	cout << b << " " << d;
}

