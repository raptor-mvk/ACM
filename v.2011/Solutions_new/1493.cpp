#include <iostream>

using namespace std;

const int DIGITS_COUNT=3;

int main() {
	char c;
	int left=0,right=0;
	for(int i=0;i<DIGITS_COUNT;i++) {
		cin>>c;
		left+=c-'0';
	}
	for(int i=0;i<DIGITS_COUNT;i++) {
		cin>>c;
		right+=c-'0';
	}
	if((left-right==1)&&(c!='9')||(left-right==-1)&&(c != '0'))
		cout<<"Yes";
	else
		cout<<"No";
}
