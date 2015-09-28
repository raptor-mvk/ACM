// Topic: dynamic programming
// Subtopic: one-dimensional with bignum arithmetic
// Idea: given N-digit valid number, it could be prefixed
//       with any digit except zero to form (N + 1)-digit number
//       or with any digit except zero and zero to form (N + 2)-digit number

#include "..\Tools\Huge.h"

int main() {
	int n, k;
	Huge prev, cur, next;
	cin >> n >> k;
	prev = 1;
	cur = k - 1;
	for (int i = 2; i <= n; i++) {
		next = (prev + cur) * (k - 1);
		prev = cur;
		cur = next;
	}
	cout << next;
}
