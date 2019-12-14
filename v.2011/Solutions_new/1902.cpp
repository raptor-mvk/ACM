#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int n;
	double t,s,u;
	cin>>n>>t>>s;
	for(int i=0;i<n;i++) {
		cin>>u;
		cout<<fixed<<setprecision(6)<<(s+(t-(s-u))/2)<<'\n';
	}
}
