// Topic: elementary

#include <iostream>

using namespace std;

const int TASKS = 12;
const int TIME = 45;
const int TOTAL_TIME = 240;

int main() {
  int f;
  cin >> f;
  if (TIME * (TASKS - f) < TOTAL_TIME) {
    cout << "YES";
  } else {
    cout << "NO";
  }
}
