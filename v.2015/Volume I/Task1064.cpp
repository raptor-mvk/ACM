// Topic: peculiar
// Subtopic: code analysis
// Idea: simulation

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_N = 10002;

int binarySearch(int x, int n, int *a) {
  int p, q, i, l;
  p = 0;
  q = n - 1;
  l = 0;
  while (p <= q) {
    i = (p + q) / 2;
    ++l;
    if (a[i] == x) {
			return l;
    }
    if (x < a[i]) {
      q = i - 1;
    } else {
      p = i + 1;
    }
  }
	return -1;
}

int main() {
	int *a, intervalsCount = 0, l, i, j;
	bool *nVal;
	cin >> i >> l;
	a = new int[MAX_N];
	nVal = new bool[MAX_N];
	memset(nVal, false, sizeof(bool)*MAX_N);
	for (j = 0; j < MAX_N - 1; j++) {
		a[j] = j;
		if (j >= i && binarySearch(i, j, a) == l) {
			nVal[j] = true;
			if (!nVal[j - 1]) {
        intervalsCount++;
			}
		}
	}
	cout << intervalsCount << '\n';
	for (j = 1; j < MAX_N; j++) {
		if (nVal[j] && !nVal[j - 1]) {
        cout << j << ' ';
		}
		if (!nVal[j + 1] && nVal[j]) {
      cout << j << '\n';
		}
	}
}
