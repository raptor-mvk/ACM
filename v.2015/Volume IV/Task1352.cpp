// Topic: peculiar
// Subtopic: problem text analysis

#include <iostream>
#include <cmath>

using namespace std;

const int MAX_N = 38;
const int MERSENNE[MAX_N] = {31, 61, 89, 107, 127, 521, 607, 1279, 2203, 2281,
                             3217, 4253, 4423, 9689, 9941, 11213, 19937, 21701,
                             23209, 44497, 86243, 110503, 132049, 216091,
                             756839, 859433, 1257787, 1398269, 2976221,
                             3021377, 6972593};

bool isPrime(int n) {
  bool result = false;
  if (n % 2) {
    result = true;
    for (int i = 3, count = (int)floor(sqrt((double)n)); i <= count; i += 2) {
      if (!(n % i)) {
        result = false;
        break;
      }
    }
  }
  return result;
}

int main() {
  int k, n, *low;
  low = new int[7];
  low[0] = 2;
  low[1] = 3;
  k = 2;
  for (int j = 4; j < 31; j++) {
    if (isPrime((int)pow(2.0, j) - 1)) {
      low[k++] = j;
    }
  }
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> k;
    if (k < 8) {
      cout << low[k - 1] << '\n';
    } else {
      cout << MERSENNE[k - 8] << '\n';
    }
  }
}
