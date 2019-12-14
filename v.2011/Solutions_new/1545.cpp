#include <iostream>

using namespace std;

int main() {
	int n;
	char symbol,*first,*second;
	cin>>n;
	cin.ignore(1,'\n');
	first=new char[n];
	second=new char[n];
	for(int i=0;i<n;i++) {
		cin>>first[i]>>second[i];
		cin.ignore(1,'\n');
	}
	cin>>symbol;
	for(int i=0;i<n;i++)
		if(first[i]==symbol)
			cout<<first[i]<<second[i]<<'\n';
}
