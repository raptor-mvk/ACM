#include <iostream>

using namespace std;

int main() {
  int x,y;
  cin>>x>>y;
  if((x>0)&&(y>0)&&((x+y)%2))
    cout<<y<<' '<<x;
  else
    cout<<x<<' '<<y;
}