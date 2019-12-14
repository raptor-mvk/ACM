// Topic: arithmetic
// Subtopic: elementary
// Idea: full search from the end of segment to its beginning,
//       if a prime is found, then it is the answer

#include <iostream>

using namespace std;

int main() {
	int i, j, cur, mink;
	double min;
	cin >> i >> j;
	min = (double)j;
	if (i == 1) {
		cout << 1;
	} else if (i == j) {
    cout<<i;
	}	else {
		for (int k = j; k >= i; k--) {
			if (k % 2) {
        cur = 1;
        for (int l = 2; l * l <= k; l++)
          if (!(k % l)) {
            cur += l;
            if (l * l != k)
              cur += k / l;
          }
        if (cur == 1) {
          cout << k;
          break;
        }
        if (min > (double)cur / k) {
          min = (double)cur / k;
          mink = k;
        }
      }
      if (k == i) {
        cout << mink;
      }
    }
	}
}
