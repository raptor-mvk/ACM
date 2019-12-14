// Topic: math
// Subtopic: Gaussian elimination
// Idea: define A[i][j] = 1, if j-th technician turns i-th valve, and 0
//       otherwise, then we have an equation A * x = I, where I – vector of
//       ones

#include "../Tools/MVector.h"
#include <iostream>
#include <cstring>

int main() {
  char *ans;
  int n,cur;
  cin >> n;
  vector2<char> matrix(n, n);
	ans = new char[n];
  memset(ans, 1, n * sizeof(char));
  for (int i = 0; i < n; i++) {
		cin >> cur;
    while (cur != -1) {
      matrix[cur - 1][i] = 1;
      cin >> cur;
    }
  }
  for (int i = 0; i < n - 1; i++) {
    if (matrix[i][i]) {
      for (int j = i + 1; j < n; j++) {
        if (matrix[j][i]) {
          for (int k = 0; k < n; k++) {
            matrix[j][k] ^= matrix[i][k];
          }
          ans[j] ^= ans[i];
        }
      }
    } else {
      int j = i;
      while (!matrix[++j][i]);
      for (int k = 0; k < n; k++) {
        matrix[i][k] ^= matrix[j][k];
      }
      ans[i] ^= ans[j];
      for (; j < n; j++) {
        if (matrix[j][i]) {
          for (int k = 0; k < n; k++) {
            matrix[j][k] ^= matrix[i][k];
          }
          ans[j] ^= ans[i];
        }
      }
    }
  }
  for (int i = n - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (matrix[j][i]) {
        for (int k = 0; k < n; k++)
          matrix[j][k] ^= matrix[i][k];
        ans[j] ^= ans[i];
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (ans[i]) {
			cout << (i + 1) << ' ';
    }
  }
}
