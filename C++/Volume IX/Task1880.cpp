// Topic: elementary

#include <iostream>

using namespace std;

int main()
{
  int n1, n2, cur, count, j;
  int *numbers;
  cin >> n1;
  numbers = new int[n1];
  for (int i = 0; i < n1; i++) {
    cin >> numbers[i];
  }
  count = n1;
  for (int k = 0; k < 2; k++) {
    cin >> n2;
    j = 0;
    for (int i = 0; i < n2; i++) {
      cin >> cur;
      while (j < n1 && cur > numbers[j]) {
        if (numbers[j]) {
          count--;
        }
        numbers[j++] = 0;
      }
      if(j < n1 && cur == numbers[j]) {
        j++;
      }
    }
    while (j < n1) {
      numbers[j++] = 0;
      count--;
    }
  }
  cout<<count;
}
