/*
  http://acm.timus.ru/problem.aspx?space=1&num=1048
  #easy #math
*/

#include <iostream>

using namespace std;

int main() {
	reader *r;
  int n,size,d1,d2;
  char *str,*sum,t,t2;
  cin>>n;
  size=4*n+1;
  sum=new char[n];
	str=new char[size];
	r=new reader(cin,str,size);
	r->fill();
  t=0;
  for(int i=0;i<n;i++) {
    r->getNext<int>(&d1,'f',false);
    r->getNext<int>(&d2,'f',false);
    sum[i]=(d1+d2+t)%10+'0';
    t=(d1+d2+t)/10;
    for(int j=-1;t>0;j--) {
      t2=((sum[i+j]-'0')+t)%10;
      t=((sum[i+j]-'0')+t)/10;
      sum[i+j]=t2+'0';
    }
  }
  cout.write(sum,n);
}
