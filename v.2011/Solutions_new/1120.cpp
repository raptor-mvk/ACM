#include <iostream>

using namespace std;

int main() {
	int n,sum=1,a,p;
	bool found=false;
	cin>>n;
	for(int i=2;sum<n;i++) {
		sum=sum+i;
		if(!((n-sum)%i)) {
			found=true;
			p=i;
			a=(n-sum)/i+1;
		}
	}
	if(found)
		cout<<a<<' '<<p;
	else
		cout<<n<<" 1";
}
