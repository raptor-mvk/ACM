// Topic: sort methods
// Subtopic: bucket sort

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_DIFF = 101;

int main() {
  int n, answer = 0, cur, count[MAX_DIFF];
  cin >> n;
  memset(count, 0, MAX_DIFF * sizeof(int));
  for (int i = 0; i < n; i++) {
    cin >> cur;
    count[cur - 600]++;
    if (!(count[cur - 600] & 3)) {
      answer++;
    }
  }
  cout << answer;
}
