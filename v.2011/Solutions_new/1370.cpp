#include <iostream>

using namespace std;

const int DIGITS_COUNT=10;

int main() {
  int n,m;
  char *wheel;
  cin>>n>>m;
  wheel=new char[n];
  for(int i=0;i<n;i++)
    cin>>wheel[i];
  for(int i=0;i<DIGITS_COUNT;i++)
    cout<<wheel[(i+m)%n];
}
