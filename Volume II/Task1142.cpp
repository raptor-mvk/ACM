// Topic: math
// Subtopic: combinatorics
// Idea: The answer is the number of ordered groupings from n elements

#include <iostream>
#include "../Tools/Calculator.h"

const int MAX_N=10;

int main() {
  int n, values[MAX_N];
  for(int i = 0; i < MAX_N; i++)
    values[i] = Calculator::ordGroupCount(i + 1);
  cin >> n;
  while(n != -1) {
    cout << values[n - 1] << '\n';
    cin >> n;
  }
}
