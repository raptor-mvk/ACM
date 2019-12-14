#include <iostream>

using namespace std;

int main() {
  int n;
	long long *ans;
  cin>>n;
  ans=new long long[n];
  ans[0]=2;
  ans[1]=2;
  for(int i=2;i<n;i++)
    ans[i]=ans[i-2]+ans[i-1];
  cout<<ans[n-1];
}
