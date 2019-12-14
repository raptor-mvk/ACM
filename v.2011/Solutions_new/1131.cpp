#include <iostream>

using namespace std;

int main() {
	int n,k,cur=1,count=0;
	cin>>n>>k;
	while((cur<k)&&(cur<n)) {
		cur*=2;
		count++;
	}
	if(cur<n)
		cout<<count+(n-cur)/k+((n-cur)%k?1:0);
	else
		cout<<count;
}
