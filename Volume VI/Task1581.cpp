// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

int main() {
  int n, cur, prev, count=1;
  cin >> n >> prev;
  for (int i = 1; i < n; i++) {
    cin >> cur;
    if (cur == prev) {
      count++;
    } else {
      cout << count << ' ' << prev << ' ';
      count = 1;
    }
    prev = cur;
  }
  cout << count << ' ' << prev;
}
