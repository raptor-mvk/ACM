// Topic: games
// Subtopic: deterministic strategy
// Idea: if N is winning position, then all N + k(i) are losing positions

#include <iostream>
#include <cstring>

using namespace std;

int main() {
  int n, m, *k;
	char *pos;
  cin >> n >> m;
  k = new int[m];
	pos = new char[n + 1];
	memset(pos, 0, n + 1);
  for (int i = 0; i < m; i++) {
    cin >> k[i];
  }
  pos[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++) {
      if (i - k[j] >= 0 && pos[i - k[j]] == 2) {
        pos[i] = 1;
        break;
      }
    }
    if (!pos[i]) {
      pos[i] = 2;
    }
  }
  cout << (int)pos[n];
}
