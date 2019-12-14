#include <iostream>

using namespace std;

int main() {
  int m,n;
  cin>>m>>n;
  cout<<((m==1)?(n/2+(n%2)):((n==1)?(m/2+(m%2)):(1+(!(m%3)||!(n%3)))));
}