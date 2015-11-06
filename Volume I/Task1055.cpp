// Topic: arithmetic
// Subtopic: elementary
// Idea: sum prime dividers powers from m to n and subscribe prime dividers
//       powers from 1 to n - m

#include "../Tools/Calculator.h"
#include <iostream>

void updateDividers(vector<int> *dividers, vector<int> *cur) {
  if (cur->size() > dividers->size()) {
    for (unsigned int i = 0; i < dividers->size(); i++) {
      (*dividers)[i] += (*cur)[i];
    }
    for (unsigned int i = dividers->size(); i < cur->size(); i++) {
      dividers->push_back((*cur)[i]);
    }
  } else {
    for (unsigned int i = 0; i < cur->size(); i++) {
      (*dividers)[i] += (*cur)[i];
    }
  }
}

int main() {
  int n, m, dividersCount = 0;
  Calculator calc;
  vector<int> dividers, cur;
  cin >> n >> m;
	for (int i = (n - m > m ? n - m : m); i < n; i++) {
    cur.clear();
    calc.getPrimeDividersPowers(i + 1, &cur);
    updateDividers(&dividers, &cur);
	}
	for (int i = 0, count = (n - m > m ? m : n - m); i < count; i++) {
    cur.clear();
    calc.getPrimeDividersPowers(i + 1, &cur);
    for (int j = 0, count = cur.size(); j < count; j++) {
      cur[j] = - cur[j];
    }
    updateDividers(&dividers, &cur);
	}
  for (int j = 0, count = dividers.size(); j < count;j++) {
    if (dividers[j]) {
      dividersCount++;
    }
  }
  cout << dividersCount;
}
