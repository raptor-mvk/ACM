#include <iostream>

using namespace std;

const int TRUCK_SIZE=36;

int main() {
	int n,*a,max=0,cur=0;
	cin>>n;
	a=new int[n*n];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>a[i*n+j];
	for(int i=0;i<n;i++) {
		for(int j=i+1;j<n;j++)
			cur+=a[i*n+j];
		for(int j=0;j<i;j++)
			cur-=a[j*n+i];
		if(cur>max)
			max=cur;
	}
	for(int i=n-1;i>=0;i--) {
		for(int j=i-1;j>=0;j--)
			cur+=a[i*n+j];
		for(int j=i;j<n;j++)
			cur-=a[j*n+i];
		if(cur>max)
			max=cur;
	}
	cout<<(max/TRUCK_SIZE+((max%TRUCK_SIZE)?1:0));
}
