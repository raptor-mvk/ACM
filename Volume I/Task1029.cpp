// Topic: dynamic programming
// Subtopic: two-dimensional
// Idea: define C[i][j] - cost of signing document from 1st floor to room
//       (i, j), F[i][j] - fee for signing document in room (i, j),
//       then C[m - 1][j] = F[m - 1][j]; for each i from m - 2 to 0:
//       C[i][0] = C[i + 1][0] + F[i][0]
//       for each j from 1 to n - 1 a first approximation is
//       C[i][j] = min (C[i][j - 1]; C[i + 1][j]) + F[i]
//       then for each j from n - 2 to 0:
//       C[i][j] = min (C[i][j]; C[i][j + 1] + F[i][j])

#include "../Tools/MVector.h"
#include <iostream>

using namespace std;

const int MIN_FEE=2000000000;

int main() {
	int m, n, jNext, min = MIN_FEE, iMin;
	cin >> m >> n;
	vector2<int> ministry(m, n), cost(m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> ministry[i][j];
		}
	}
	for (int j = 0; j < n; j++) {
		cost[m - 1][j] = ministry[m - 1][j];
	}
	for (int i = m - 2; i >= 0; i--) {
		cost[i][0] = cost[i + 1][0] + ministry[i][0];
		for (int j = 1; j < n; j++) {
			cost[i][j] = (cost[i][j - 1] > cost[i + 1][j] ?
				cost[i + 1][j] : cost[i][j - 1]) + ministry[i][j];
		}
		for (int j = n - 1; j > 0; j--) {
			if (cost[i][j] + ministry[i][j - 1] < cost[i][j - 1]) {
				cost[i][j - 1] = cost[i][j] + ministry[i][j - 1];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (cost[0][i] < min) {
			min = cost[0][i];
			iMin = i;
		}
	}
	cout << (iMin + 1) << ' ';
	for (int i = 1; i < m - 1;) {
		if (cost[i][iMin] == cost[i + 1][iMin] + ministry[i][iMin]) {
			cout << (iMin + 1) << ' ';
			i++;
		} else {
			jNext = iMin;
			while (jNext > 0 && cost[i][jNext] == cost[i][jNext - 1] +
				ministry[i][jNext]) {
					jNext--;
      }
			if (cost[i][jNext] == cost[i + 1][jNext] + ministry[i][jNext]) {
				for(;iMin >= jNext;iMin--) {
					cout << (iMin + 1) << ' ';
				}
				i++;
				iMin++;
			} else {
				while (iMin < n && cost[i][iMin] == cost[i][iMin + 1] +
           ministry[i][iMin]) {
						cout << ((iMin++) + 1) << ' ';
        }
				cout << (iMin + 1) << ' ';
				i++;
			}
		}
	}
	if (m > 1) {
		cout << (iMin + 1);
	}
}
