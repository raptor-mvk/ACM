#include <iostream>

using namespace std;

int main() {
	int n,*in;
	cin>>n;
	in=new int[n*n];
	for(int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			cin>>in[n*i+j];
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++)
			cout<<in[n*(i-j)+j]<<' ';
	for(int i=1;i<n;i++)
		for (int j=i;j<n;j++)
			cout<<in[n*(n-1-(j-i))+j]<<' ';
}
