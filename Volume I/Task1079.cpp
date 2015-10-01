// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

const int MAX_N = 100001;

int main() {
	int n, a[MAX_N], v[MAX_N];
	a[0] = 0;
	a[1] = 1;
	for (int i = 2; i < MAX_N; i++) {
		if (!(i % 2)) {
			a[i] = a[i / 2];
		} else {
			a[i] = a[i / 2] + a[i / 2 + 1];
		}
	}
	v[0] = 0;
	v[1] = 1;
	for (int i = 2; i < MAX_N; i++) {
		if (!(i % 2)) {
			v[i] = v[i - 1];
		} else {
			v[i] = v[i - 2] > a[i] ? v[i - 2] : a[i];
		}
	}
	cin >> n;
	while (n) {
		cout << v[n] << '\n';
		cin >> n;
	}
}
