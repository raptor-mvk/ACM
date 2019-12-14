#include <iostream>

using namespace std;

int main() {
  int d,e,f,h,dp,ep,level,cur=1,max;
  cin>>d>>e>>f>>dp>>ep>>h;
  level=f;
  cur<<=f-1;
  max=(e>d)?e:d;
  while((level>0)&&(((dp-1)&cur)==((ep-1)&cur))) {
    level--;
    cur>>=1;
  }
  if(level>max) {
    if(level-d+level-e>h)
      cout<<"NO";
    else
      cout<<"YES";
  }
  else {
    if(abs(e-d)>h)
      cout<<"NO";
    else
      cout<<"YES";
  }
}