#include <iostream>

using namespace std;

int main() {
	int n,*locker,cur_number=1;
	cin>>n;
	locker=new int[n*n];
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++)
			locker[n*(i-j)+j]=cur_number++;
	for(int i=1;i<n;i++)
		for(int j=i;j<n;j++)
			locker[n*(n-1-(j-i))+j]=cur_number++;
	for(int i=0;i<n;i++) {
		for (int j=n-1;j>=0;j--)
			cout<<locker[n*j+i]<<' ';
		cout<<'\n';
	}
}
