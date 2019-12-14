// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

int main() {
  int n, cur = 1, count = 0;
  cin >> n;
  while (cur < n) {
    cur <<= 1;
    count++;
  }
  cout << count << '\n';
  while (count-- > 0) {
    cout << ((n >> 1) + (n & 1)) << ' ';
    n = (n >> 1) + (n & 1);
  }
}
