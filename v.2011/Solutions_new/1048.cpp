#include <iostream>

using namespace std;

int main() {
  int n;
  char *str,*sum,t,t2;
  cin>>n;
  cin.ignore(1,'\n');
  str=new char[4*n];
  sum=new char[n];
  cin.getline(str,4*n,EOF);
  for(int i=0;i<n;i++) {
    sum[i]=(str[i*4]-'0'+str[i*4+2]-'0'+t)%10+'0';
    t=(str[i*4]-'0'+str[i*4+2]-'0'+t)/10;
    for(int j=-1;t>0;j--) {
      t2=((sum[i+j]-'0')+t)%10;
      t=((sum[i+j]-'0')+t)/10;
      sum[i+j]=t2+'0';
    }
  }
  cout.write(sum,n);
}
