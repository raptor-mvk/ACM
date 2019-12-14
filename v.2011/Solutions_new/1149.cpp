#include <iostream>

using namespace std;

void printA(int n,int k) {
	if (n==k) {
		cout<<"sin("<<n<<')';
		return;
	}
	cout<<"sin("<<k;
	if(k%2)
		cout<<'-';
	else
		cout<<'+';
	printA(n,k+1);
	cout<<')';
}

void printS(int n,int k) {
	if(n==1) {
		printA(1, 1);
		cout<<'+'<<k;
		return;
	}
	cout<<'(';
	printS(n-1,k+1);
	cout<<')';
	printA(n,1);
	cout<<'+'<<k;
}

int main() {
	int n;
	cin>>n;
	printS(n,1);
}