#include <iostream>
#include <cmath>

using namespace std;

int main() {
  int r;
  long long answer=0;
  cin>>r;
  for(int i=0;i<r;i++)
    answer+=(long long)ceil(sqrt((double)r*(double)r-(double)i*(double)i));
  cout<<(answer*4);
}