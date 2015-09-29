// Topic: math
// Subtopic: graph of function
// Idea: B - A could be 1

#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int n;
	long long A, B, mi, ci, cur, prev;
	cin >> n >> A >> B;
	mi = abs(B - A);
	prev = B;
	A = 1;
	B = 2;
	for (int i = 2; i < n; i++) {
		cin >> cur;
		ci = abs(cur - prev);
		if (ci > mi) {
			mi = ci;
			A = i;
			B = i + 1;
		}
		prev = cur;
	}
	cout << A << ' ' << B << '\n';
}
