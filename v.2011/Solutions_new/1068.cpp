#include <iostream>

using namespace std;

int main() {
  int n;
  cin>>n;
  if(!n)
    cout<<1;
  else
    cout<<((n>0)?(((1+n)*n)/2):(((2+abs(n))*(1-abs(n)))/2));
}