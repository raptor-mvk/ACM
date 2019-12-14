#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int n,k,*numbers;
	cin>>n>>k;
	numbers=new int[n];
	for(int i=0;i<n;i++)
		cin>>numbers[i];
	for(int i=0;i<n/k+(n%k!=0);i++)	{
		for(int j=i;j<n;j+=n/k+(n%k!=0))
			if(!numbers[j])
				cout<<setw(4)<<0;
			else
				cout<<setw(4)<<numbers[j];
		cout<<'\n';
	}
}
