// Topic: dynamic programming
// Subtopic: two-dimensional
// Idea: number of staircases S[N,K] from exactly N bricks with largest step
//       of K bricks is calculated as sum S[N - K, I],
//       where I runs from 1 to K - 1

#include <iostream>
#include "../Tools/MVector.h"

int main() {
	int n;
	long long res = -1;
	vector2<long long> count;
	cin >> n;
	count.assign(n, n);
	for (int i = 0; i < n; i++) {
		count[i][i] = 1;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			for (int k = 0; k < j; k++) {
				count[i][j] += count[i - j - 1][k];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		res += count[n - 1][i];
	}
	cout << res;
}
