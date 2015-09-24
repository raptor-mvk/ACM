// Topic: math
// Subtopic: reverse Polish notation

#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  cout << "0\n";
  for (int i = 0; i < n; i++)
    cout << "X\n*\n" << (i + 1) << "\n+\n";
}
