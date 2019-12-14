// Topic: games
// Subtopic: directly calculated winning positions
// Idea: second player wins if there is remainder of division N by K

#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  for (int i = 2; i < n; i++) {
    if (!(n % (i + 1))) {
      cout << i;
      break;
    }
  }
}
