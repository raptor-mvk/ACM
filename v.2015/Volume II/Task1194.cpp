// Topic: arithmetic
// Subtopic: progressions
// Idea: Each two hobbits will shake hands except married couples

#include <iostream>

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;
  cout << (n * (n - 1) / 2 - k);
}
