#include <iostream>

using namespace std;

int main() {
	int n,k;
	long long *count;
	cin>>n>>k;
	count=new long long[n+1];
	count[0]=1;
	count[1]=k-1;
	for(int i=2;i<=n;i++)
		count[i]=(long long)(k-1)*(count[i-1]+count[i-2]);
	cout<<count[n];
}
