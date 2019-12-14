#include <iostream>

using namespace std;

int MAX_N=11111;
int MAGIC_KEY=153;

int main() {
  int *keys;
  int cur_key,cur_num,t,n,k,l;
  keys=new int[MAX_N];
  for(int i=0;i<MAX_N;i++) {
    cur_num=(i+1)*3;
    cur_key=0;
    while(cur_num) {
      cur_key+=(cur_num%10)*(cur_num%10)*(cur_num%10);
      cur_num/=10;
    }
    keys[i]=cur_key;
  }
  cin>>t;
  for(int i=0;i<t;i++) {
		cin>>n>>k>>l;
    if(n==1)
			cout<<(k-l)<<'\n';
    else {
      cur_key=k;
      for(int j=1;j<n;j++) {
        cur_key=keys[cur_key/3-1];
        if(cur_key==MAGIC_KEY)
					break;
      }
      cout<<(cur_key-l)<<'\n';
    }
  }
}
