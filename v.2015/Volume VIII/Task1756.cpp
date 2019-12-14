// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

int main() {
  int m, d1, d2;
  cin >> m >> d1 >> d2;
  for(int i = 0; i < d2; i++) {
    if (i < m * d1 % d2) {
      cout << (m * d1 / d2 + 1) << ' ';
    } else {
      cout << (m * d1 / d2) << ' ';
    }
  }
}
