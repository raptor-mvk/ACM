// Topic: dynamic programming
// Subtopic: one-dimensional
// Idea: given N quadrics, the minimum M[n] is taken from values
//       M[n - 1] + 1, M[n - 4] + 1, ..., M[n - k * k] + 1

#include <iostream>

using namespace std;

int main() {
  int n, cur_min, *count;
  cin >> n;
  count = new int[n + 1];
  count[0] = 0;
  for (int i = 1; i <= n; i++) {
    cur_min = i;
    for (int j = 1; j * j <= i; j++) {
      if (count[i - j * j] + 1 < cur_min) {
        cur_min = count[i - j * j] + 1;
      }
    }
    count[i] = cur_min;
  }
  cout << count[n];
}
