#include <iostream>

using namespace std;

int main() {
  int m,n;
  cin>>m>>n;
  if(!(m&1)||!(n&1))
    cout<<"[:=[first]";
  else
    cout<<"[second]=:]";
}