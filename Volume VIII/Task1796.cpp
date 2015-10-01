// Topic: arithmetic
// Subtopic: elementary
// Idea: let d - denomination of minimal note, then number of tickets
//       should be between (s - d) / t + 1 and s / t

#include <iostream>

using namespace std;

const int NOTES_COUNT = 6;
const int NOTES[NOTES_COUNT] = {10, 50, 100, 500, 1000, 5000};

int main() {
  int sum = 0, diff = 0, ticket;
  for (int i = 0; i < NOTES_COUNT; i++) {
    cin >> ticket;
    sum += ticket * NOTES[i];
    if (ticket && !diff) {
      diff = NOTES[i];
    }
  }
  cin >> ticket;
  cout << (sum / ticket - (sum - diff) / ticket) << '\n';
  for (int i = (sum - diff) / ticket + 1; i <= sum / ticket; i++) {
    cout << i << ' ';
  }
}

