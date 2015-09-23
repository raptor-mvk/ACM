// Topic: arithmetic
// Subtopic: elementary
// Idea: worm doesn't gnaw first and last volumes themselves, moving right
//       on the other hand, it gnaws both first and last volumes themselves,
//       moving left

#include <iostream>

using namespace std;

int main() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  cout << abs(((d - c) * (2 * b + a) - a));
}
