// Topic: arithmetic
// Subtopic: progressions

#include <iostream>
#include <cmath>

using namespace std;

int main() {
  int n;
  cin >> n;
  if (!n) {
    cout << 1;
  } else {
    cout << (n > 0 ? (n + 1) * n / 2 : (abs(n) + 2) * (1 - abs(n)) / 2);
  }
}
