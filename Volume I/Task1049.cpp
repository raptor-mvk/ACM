// Topic: math
// Subtopic: coding theory

#include <iostream>
#include "../Tools/Calculator.h"

const int NUMBERS_COUNT = 10;

int main() {
  Calculator calculator;
	int n, answer = 1;
  vector<int> dividers, cur;
	for (int i = 0; i < NUMBERS_COUNT; i++) {
    cin>>n;
    calculator.getPrimeDividersPowers(n, &cur);
    if (cur.size() > dividers.size()) {
      for (unsigned int i = 0; i < dividers.size(); i++) {
        dividers[i] += cur[i];
      }
      for (unsigned int i = dividers.size(); i < cur.size(); i++) {
        dividers.push_back(cur[i]);
      }
    } else {
      for (unsigned int i = 0; i < cur.size(); i++) {
        dividers[i] += cur[i];
      }
    }
	}
	for (unsigned int i = 0; i < dividers.size(); i++) {
    answer *= dividers[i] + 1;
    answer %= 10;
	}
	cout << answer;
}
