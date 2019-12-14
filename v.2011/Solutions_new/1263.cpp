#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int n,m,cur,*voices;
	cin>>n>>m;
	voices=new int[n];
	memset(voices,0,n*sizeof(int));
	for(int i=0;i<m;i++) {
		cin>>cur;
		voices[cur-1]++;
	}
	for(int i=0;i<n;i++)
		cout<<setprecision(2)<<fixed<<(double)voices[i]/m*100.0<<"%\n";
}
