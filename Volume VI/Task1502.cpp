// Topic: arithmetic
// Subtopic: progressions
// Idea: Each number of points occurred N+2 times

#include <iostream>

using namespace std;

int main() {
  long long n;
  cin >> n;
  cout << (((n + 2) * (n + 1) * n) / 2);
}
