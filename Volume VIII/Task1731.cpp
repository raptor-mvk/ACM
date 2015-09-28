// Topic: arithmetic
// Subtopic: elementary
// Idea: boxes with first sort could be 1, ..., n
//       and boxes with second sort could be 1 * (n + 1), ..., m * (n + 1)

#include <iostream>

using namespace std;

int main() {
  int m, n;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cout << i << ' ';
  }
  cout << '\n';
  for (int i = 1; i <= m; i++) {
    cout << (i * (n + 1)) << ' ';
  }
}
