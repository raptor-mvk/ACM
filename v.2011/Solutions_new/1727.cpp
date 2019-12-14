#include <iostream>

using namespace std;

const int MAX_DIFF=45;
const int MULT=10;
const int DIFF_FINISH=9;
const int LAST_LENGTH=5;

int main() {
  int n,s=0,i=1,cur,count;
  cin>>n;
  while(n-s>MAX_DIFF) {
    cur=i++;
    while(cur) {
      s+=cur%MULT;
      cur/=MULT;
    }
  }
  count=i;
  cout<<i<<'\n';
  for(cur=1;cur<i;cur++)
    cout<<cur<<' ';
  cur=0;
  while(n-s>DIFF_FINISH) {
    s+=DIFF_FINISH;
    cur++;
    cout<<9;
  }
  cout<<n-s;
  while(++cur<LAST_LENGTH)
    cout<<0;
}
