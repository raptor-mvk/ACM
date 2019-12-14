#include <iostream>

using namespace std;

int main() {
	int n,m,cur;
	long long sum=0;
	cin>>n>>m;
	for(int i=0;i<m;i++) {
		cin>>cur;
		sum+=(long long)cur;
		if(sum>(long long)n*3) {
			cout<<"Free after "<<(i+1)<<" times.";
			break;
		}
	}
	if(sum<=(long long)n*3)
		cout<<"Team.GOV!";
}
