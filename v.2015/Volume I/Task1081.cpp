// Topic: dynamic programming
// Subtopic: one-dimensional
// Idea: sequence with length i could be gotten by two ways
//       1. add 0 to sequence with length i - 1
//       2. add 01 to sequence with length i - 2
//       k-th sequence with length n is produced by algorithm:
//       1. while n > 0
//         a. find sequence with length n1 such, that the number of
//            sequences with length n1 - 1 is greater than or equal to k
//         b. print n1 - n zeros
//         c. n = n1
//         d. if K > 2, then
//           i. k = k - the number of sequences with length n1 - 2
//           ii. if n = 1, then print 1, else print 10
//           iii. n = n - 2
//         e. if k = 2, then
//           i. print 1
//           ii. n = 0
//         f. if k = 1, then
//           i. n = 0
//           ii. print n1 zeros

#include <iostream>

using namespace std;

int main() {
  int i, n, k, *numbers_count;
  cin >> n >> k;
  numbers_count = new int[n];
  numbers_count[0] = 2;
  numbers_count[1] = 3;
  for (int j = 2; j < n; j++) {
    numbers_count[j] = numbers_count[j - 1] + numbers_count[j - 2];
  }
  if (k <= numbers_count[n - 1]) {
    while (n > 0) {
      i = 0;
      while (numbers_count[i++] < k);
      for (int j = i; j < n; j++) {
        cout << 0;
      }
      n = i;
      if (k > 2) {
        k -= numbers_count[i - 2];
        if (n == 1) {
          cout << "1";
        } else {
          cout << "10";
        }
        n -= 2;
      } else {
        n = 0;
        if (k == 1) {
          for (; i > 0; i--) {
            cout << "0";
          }
        } else {
          cout << "1";
        }
      }
    }
  }
  else {
    cout << "-1";
  }
}
