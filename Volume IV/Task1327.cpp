/*
  http://acm.timus.ru/problem.aspx?space=1&num=1327
  if both a and b are even, then answer is (b - a) / 2
  if either a, or b is odd, then answer is (b - a + 1) / 2
  if both a and b are odd, then answer is (b - a) / 2 + 1
*/

#include <iostream>

using namespace std;

int main() {
  int a,b;
  cin>>a>>b;
  cout<<((b+(b%2)-(a-(a%2)))/2);
}
