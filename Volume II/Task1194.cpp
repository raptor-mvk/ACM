/*
  http://acm.timus.ru/problem.aspx?space=1&num=1194
  Each two hobbits will shake hands except married couples
*/

#include <iostream>

using namespace std;

int main() {
  int n,k;
  cin>>n>>k;
  cout<<(n*(n-1)/2-k);
}
