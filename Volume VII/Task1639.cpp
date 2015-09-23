// Topic: game
// Subtopic: simple
// Idea: if both m and n are even, then Karlsson should start the game,
//       otherwise Little Boy should

#include <iostream>

using namespace std;

int main() {
  int m, n;
  cin >> m >> n;
  if (!(m & 1) || !(n & 1)) {
    cout << "[:=[first]";
  } else {
    cout << "[second]=:]";
  }
}
