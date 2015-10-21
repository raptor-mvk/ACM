#include "Calculator.h"

Calculator::Calculator() {
  primes.push_back(2);
  primes.push_back(3);
  lastPrime = 3;
}

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

int Calculator::getNextPrime() {
  int result = lastPrime + 2;
  bool found = false;
  while (!found) {
    found = true;
    for (int j = 0, count = (int)floor(sqrt(result)); primes[j] <= count; j++) {
      if (!(result % primes[j])) {
        found = false;
        result += 2;
        break;
      }
    }
  }
  return result;
}

void Calculator::calcPrimes(int n) {
  while (n > lastPrime) {
    int nextPrime = getNextPrime();
    lastPrime = nextPrime;
    primes.push_back(nextPrime);
  }
}

vector<int> *Calculator::getPrimes(int n) {
  calcPrimes(n);
  return &primes;
}

void Calculator::getPrimeDividers(int n, vector<int> *result) {
  calcPrimes(n);
  int j = 0;
  while (n > 1) {
    if (!(n % primes[j])) {
      result->push_back(primes[j]);
      n /= primes[j];
    } else {
      j++;
    }
  }
}

void Calculator::getPrimeDividersPowers(int n, vector<int> *result) {
  calcPrimes(n);
  result->assign(primes.size(), 0);
  int j = 0;
  while (n > 1) {
    if (!(n % primes[j])) {
      (*result)[j]++;
      n /= primes[j];
    } else {
      j++;
    }
  }
}
