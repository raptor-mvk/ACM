// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

int main() {
  int n, k = 0;
  long long res = 1;
  char c;
  cin >> n;
  cin.ignore(1);
  cin.get(c);
  while (!cin.eof() && (c == '!')) {
    k++;
    cin.get(c);
  }
  while (n > 0) {
    res *= (long long)n;
    n -= k;
  }
  cout << res;
}
