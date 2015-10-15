// Topic: arithmetic
// Subtopic: elementary
// Idea: full search

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_L = 10000;

int main() {
  int n, m, k, max;
  int count[MAX_L];
  cin >> m >> n >> k;
  memset(count, 0, MAX_L * sizeof(int));
  for (int i = 0; i < MAX_L; i++) {
    max = (int)(floor(sqrt((double)(i + 1))));
    for (int j = 1; j <= max; j++) {
      if (!((i + 1) % j)) {
				count[i]++;
      }
    }
  }
  for (int i = k; i <= MAX_L; i++) {
    if (i == MAX_L) {
			cout << 0;
    }
    if ((count[i] == n) && (count[i - k] == m)) {
			cout << (i + 1);
      break;
	  }
  }
}
