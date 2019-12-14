#include <iostream>

using namespace std;

int main() {
	int n;
	long long *count,res=-1;
	cin>>n;
	count=new long long[n*n];
	memset(count,0,n*n*sizeof(long long));
	for(int i=0;i<n;i++)
		count[(n+1)*i]=1;
	for(int i=1;i<n;i++)
		for(int j=0;j<i;j++)
			for(int k=0;k<j;k++)
				count[n*i+j]+=count[n*(i-j-1)+k];
	for(int i=0;i<n;i++)
		res+=count[n*(n - 1)+i];
	cout<<res;
}
