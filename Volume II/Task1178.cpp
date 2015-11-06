// Topic: arithmetic
// Subtopic: elementary
// Idea: sort towns by polar angle of line, connecting i-th town to 1-st
//       and connect them by pairs

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

const int MAX_N = 10000;
const double PI = acos(-1.0);

bool comp(const pair<double, int> &i, const pair<double, int> &j) {
  return i.first < j.first;
}

int main() {
  int x[MAX_N], y[MAX_N];
  vector<pair<double, int> > angle(MAX_N);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
    angle[i].second = i + 1;
  }
  angle[0].first = 0;
  for (int i = 1; i < n; i++) {
    if (x[i] > x[0]) {
      angle[i].first = atan((double)(y[i] - y[0]) / (x[i] - x[0]));
    } else {
      angle[i].first = PI + atan((double)(y[i] - y[0]) / (x[i] - x[0]));
    }
  }
  sort(angle.begin(), angle.begin() + n, comp);
  for (int i = 0; i < n; i++) {
    if (i % 2) {
      cout << angle[i].second << '\n';
    } else {
      cout << angle[i].second << ' ';
    }
  }
}
