#include <iostream>

using namespace std;

int fast_power_mod(int x,int n,int m) {
	int result=1;
	while(n) {
		if(n&1) {
			result*=x;
			result=result%m;
		}
		x*=x;
		x=x%m;
		n>>=1;
	}
	return result;
}

int main() {
	int x,y,n,m;
	bool found=false;
	cin>>n>>m>>y;
	for(int i=0;i<m;i++)
		if(fast_power_mod(i,n,m)==y) {
			cout<<i<<' ';
			found=true;
		}
	if(!found)
		cout<<-1;
}
