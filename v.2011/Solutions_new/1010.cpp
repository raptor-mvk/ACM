#include <iostream>

using namespace std;

int main() {
	int n;
	long long A,B,maxa,cura,cur,prev;
	cin>>n>>A>>B;
	maxa=abs(B-A);
	prev=B;
	A=1;
	B=2;
	for(int i=2;i<n;i++) {
		cin>>cur;
		cura=abs(cur-prev);
		if(cura>maxa) {
			maxa=cura;
			A=i;
			B=i+1;
		}
		prev=cur;
	}
	cout<<A<<' '<<B<<'\n';
}
