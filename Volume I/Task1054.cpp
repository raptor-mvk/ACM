// Topic: arithmetic
// Subtopic: elementary
// Idea: Define r(k, s, f, t) as function, providing the answer,
//       then r(k, s, f, t) = r(k - 1, s, t, f), if the position
//       of k-th disc is s, and 2 ^ (k - 1) + r(k - 1, t, f, s),
//       if the position of k-th disc is f

#include <iostream>

using namespace std;

int stepsCount(int k, int *nums, int start, int finish, int temp) {
  int result = 0;
  if (k >= 0) {
    if (nums[k] == start) {
      result = stepsCount(k - 1, nums, start, temp, finish);
    } else if (nums[k] == finish) {
      result = stepsCount(k - 1, nums, temp, finish, start);
      if (result >= 0) {
        result += (1 << k);
      }
    } else {
      result = -1;
    }
  }
  return result;
}

int main() {
	int n, *d;
	cin >> n;
	d = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> d[i];
	}
	cout << stepsCount(n - 1, d, 1, 2, 3);
}
