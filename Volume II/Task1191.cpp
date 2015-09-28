// Topic: arithmetic
// Subtopic: elementary
// Idea: process simulation

#include <iostream>

using namespace std;

int main() {
  int l, n, k;
  cin >> l >> n;
  for (int i = 0; i < n; i++) {
    cin >> k;
    if (l < k) {
      cout << "YES";
      break;
    }
    l -= l % k;
  }
  if (l >= k) {
    cout << "NO";
  }
}
