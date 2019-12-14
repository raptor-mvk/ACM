// Topic: arithmetic
// Subtopic: progressions
// Idea: answer is 1 if and only if k = 1 + N * (N + 1) / 2

#include <iostream>
#include <cmath>

using namespace std;

const double EPS=1e-7;

int main() {
  int n, k;
  double t;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> k;
    t = sqrt(8.0 * (double)k - 7.0);
    if (abs(t - floor(t + 0.5)) > EPS) {
      cout<<"0 ";
    } else {
      cout<<"1 ";
    }
  }
}
