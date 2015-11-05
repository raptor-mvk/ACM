// Topic: arithmetic
// Subtopic: elementary

#include <iostream>
#include <cstring>

using namespace std;

const int PRIME_DIGITS = 4;
const int DIGITS[PRIME_DIGITS] = {2, 3, 5, 7};

int main() {
	int n;
	int dividers[PRIME_DIGITS];
	memset(dividers, 0, PRIME_DIGITS * sizeof(int));
	cin >> n;
	if (n == 1) {
		cout << 1;
	}	else if (n == 0) {
		cout << 10;
	} else {
    for (int i = 0; i < PRIME_DIGITS; i++) {
      while (n % DIGITS[i] == 0) {
        dividers[i]++;
        n /= DIGITS[i];
      }
    }
    if (n > 1) {
      cout << -1;
    } else {
      if ((dividers[0] % 3 == 1 && dividers[1] % 2 != 1) ||
          (dividers[0] % 3 == 2 && dividers[1] % 2 == 1)) {
        cout << 2;
      }
      if (dividers[1] % 2 == 1 && dividers[0] % 3 == 0) {
        cout << 3;
      }
      if (dividers[0] % 3 == 2 && dividers[1] % 2 != 1) {
        cout << 4;
      }
      for (int i = 1; i <= dividers[2]; i++) {
        cout << 5;
      }
      if (dividers[0] % 3 != 0 && dividers[1] % 2 == 1) {
        cout << 6;
      }
      for (int i = 1; i <= dividers[3]; i++) {
        cout << 7;
      }
      for (int i = 1; i <= dividers[0] / 3; i++) {
        cout << 8;
      }
      for (int i = 1; i <= dividers[1] / 2; i++) {
        cout << 9;
      }
    }
  }
}
