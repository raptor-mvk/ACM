// Topic: arithmetic
// Subtopic: progressions
// Idea: Each number of points occurred N+2 times, so the answer is
//      (N+2)*(1+2+...+N)=(N+2)*(N+1)*N/2

#include <iostream>

using namespace std;

int main() {
  long long n;
  cin >> n;
  cout << (((n + 2) * (n + 1) * n) / 2);
}
