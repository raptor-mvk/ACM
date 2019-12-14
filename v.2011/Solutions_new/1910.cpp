#include <iostream>

using namespace std;

int main() {
	int n,max=0,maxb,a,b,c;
	cin>>n>>a>>b;
	for(int i=2;i<n;i++) {
		cin>>c;
		if(a+b+c>max) {
			maxb=i;
			max=a+b+c;
		}
		a=b;
		b=c;		
	}
	cout<<max<<' '<<maxb;
}
