#include <iostream>

using namespace std;

int main() {
	int n,k;
	cin>>n>>k;
	if(n==2)
		cout<<0;
	else
		if(n/2>=k)
			cout<<(n-k-2);
		else
			cout<<(k-3);
}
