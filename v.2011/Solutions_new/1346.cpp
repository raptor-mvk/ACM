#include <iostream>

using namespace std;

int main() {
  int a,b,cur,prev,i,dir=0,count=1;
  cin>>a>>b>>prev;
  for(i=1;i<=b-a;i++) {
    cin>>cur;
    if(!dir)
      dir=(cur>prev)?1:((cur<prev)?-1:0);
    if((cur>prev)&&(dir<1)||(cur<prev)&&(dir>-1)) {
      if(dir)
        count++;
      dir=0;
    }
    prev=cur;
  }
  cout<<count;
}