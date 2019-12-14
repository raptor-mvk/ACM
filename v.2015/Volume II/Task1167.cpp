// Topic: dynamical programming
// Subtopic: two-dimensional
// Idea: define n[i][j] - coefficient of unhappiness for monocolored groups
//       from i-th to j-th placed into one stable, s[i][j] - coefficient of
//       unhappiness for i monocolored groups placed into j stables, then
//       s[i][0] = n[0][i],
//       s[j][i] = min(s[k][i - 1] + s[k + 1][j]; k = i - 1 .. j - 1)

#include <iostream>
#include "../Tools/MVector.h"

int main() {
  int *horses;
  int n, k, cur, next, min, cur_count, groups_count = 0;
  cin >> n >> k >> cur;
  vector2<int> stables(n, n), new_stable(n, n);
  horses = new int[n];
  cur_count = 1;
  for (int i = 1; i < n; i++) {
		cin >> next;
    if (cur == next) {
			cur_count++;
    } else {
      cur = next;
      horses[groups_count++] = cur_count;
      cur_count = 1;
    }
  }
  horses[groups_count++] = cur_count;
  for (int i = 0; i < groups_count; i++) {
    cur = 0;
    next = 0;
    for (int j = i; j < groups_count; j++) {
      if (j % 2) {
				cur += horses[j];
      } else {
				next += horses[j];
      }
      new_stable[i][j] = cur * next;
    }
  }
  for (int i = 0; i < groups_count; i++)
    stables[i][0] = new_stable[0][i];
  for (int i = 1; i < k; i++) {
    for (int j = i + 1; j < groups_count; j++) {
      min = stables[groups_count - 1][0];
      for (int l = i - 1; l < j; l++)
        if (min > stables[l][i - 1] + new_stable[l + 1][j])
          min = stables[l][i - 1] + new_stable[l + 1][j];
      stables[j][i] = min;
    }
  }
  cout << stables[groups_count - 1][k - 1];
}
