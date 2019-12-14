#include <iostream>

using namespace std;

const int MAX_N=2000;

int main() {
	int n,res[MAX_N],first[MAX_N],last[MAX_N];
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>res[i];
	for(int i=0;i<n;i++) {
		first[res[i]-1]=1;
		last[res[i]-1]=n;
		for(int j=0;j<i;j++)
			if(res[j]>res[i])
				first[res[i]-1]++;
		for(int j=i+1;j<n;j++)
			if(res[j]<res[i])
				last[res[i]-1]--;
	}
	for(int i=0;i<n;i++)
		cout<<first[i]<<' '<<last[i]<<'\n';
}
