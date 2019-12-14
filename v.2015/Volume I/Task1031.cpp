// Topic: dynamic programming
// Subtopic: one-dimensional
// Idea: cost(i) = min(cost(j) + c1 {j: dist(i, j) <= l1};
//                     cost(k) + c2 {k: dist(i, k) <= l2};
//                     cost(m) + c3 {m: dist(i, m) <= l3})

#include <iostream>

using namespace std;

int main() {
  int n, c1, c2, c3, l1, l2, l3, beg, end, cur;
  int *dists, *costs;
  cin >> l1 >> l2 >> l3 >> c1 >> c2 >> c3 >> n >> beg >> end;
  dists = new int[n];
  costs = new int[n];
  if (beg > end) {
    cur = beg;
    beg = end;
    end = cur;
  }
  dists[0] = 0;
  for (int i = 1; i < n; i++) {
  	cin >> dists[i];
  }
  costs[beg - 1] = 0;
  for (int i = beg; i < end; i++) {
    cur = c3 + costs[i - 1];
    for (int j = beg - 1; j < i; j++) {
      if (dists[i] - dists[j] <= l1) {
        if (cur > c1 + costs[j]) {
					cur = c1 + costs[j];
        }
      } else if (dists[i] - dists[j] <= l2) {
        if (cur > c2 + costs[j]) {
          cur = c2 + costs[j];
        }
      } else if (dists[i] - dists[j] <= l3) {
        if (cur > c3 + costs[j]) {
          cur = c3 + costs[j];
        }
      }
    }
    costs[i] = cur;
  }
  cout << costs[end - 1];
}
