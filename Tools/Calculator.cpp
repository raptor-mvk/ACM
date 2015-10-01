#include "Calculator.h"

int Calculator::fastExpMod(int x, int n, int m) {
  int result = 1;
  while (n) {
    if (n & 1) {
      result *= x;
      result = result % m;
    }
    x *= x;
    x = x % m;
    n >>= 1;
  }
  return result;
}
