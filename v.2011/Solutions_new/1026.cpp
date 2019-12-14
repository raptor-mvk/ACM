#include <iostream>

using namespace std;

const int DATABASE_CODE=5000;

int main() {
	int database[DATABASE_CODE];
	int n,k,t,l,j;
	cin>>n;
	memset(database,0,DATABASE_CODE*sizeof(int));
	for(int i=0;i<n;i++) {
		cin>>t;
		database[--t]++;
	}
	cin.ignore(1,'\n');
	cin.ignore(4,'\n');
	cin>>k;
	for(int i=0;i<k;i++) {
		cin>>t;
		j=0;
		l=0;
		while(j<t)
			j+=database[l++];
		cout<<l<<'\n';
	}
}
