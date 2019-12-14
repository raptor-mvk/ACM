// Topic: math
// Subtopic: probability theory
// Idea: best result is achieved, when return from all bets is the same

#include <iostream>
#include <cmath>

using namespace std;

const int BETS = 3;
const double MONEY = 1000.0;

int main() {
  double sum = 0, cur;
  for (int i = 0; i < BETS; i++) {
    cin >> cur;
    sum += 1.0 / cur;
  }
  cout << (int)floor(MONEY / sum + 0.5);
}
