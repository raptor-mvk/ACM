// Topic: elementary
// Idea: full search

#include <iostream>

using namespace std;

int main()
{
  int n, *weights, sum = 0, cur, curi, best, count;
  cin >> n;
  weights = new int[n];
  for (int i = 0; i < n; i++) {
    cin >> weights[i];
    sum += weights[i];
  }
  count = 2 << n;
  best = sum;
  for (int i = 1; i < count; i++) {
    cur = 0;
    curi = i;
    int j = 0;
    while (curi > 0) {
      if (curi & 1) {
        cur += weights[j];
      }
      curi >>= 1;
      j++;
    }
    if(abs(2 * cur - sum) < best) {
      best = abs(2 * cur - sum);
    }
  }
  cout << best;
}
