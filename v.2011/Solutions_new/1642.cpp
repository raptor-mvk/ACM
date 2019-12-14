#include <iostream>

using namespace std;

const int RIGHT=1001;
const int LEFT=-1001;

int main() {
	int n,right,left,exit,cur;
	cin>>n>>exit;
	if(!exit)
		cout<<"0 0\n";
	else {
		left=LEFT;
		right=RIGHT;
		for(int i=0;i<n;i++) {
			cin>>cur;
			if((cur<0)&&(cur>left))
				left=cur;
			if((cur>0)&&(cur<right))
				right=cur;
		}
		if((exit>0)&&(exit>right)||(exit<0)&&(exit<left))
			cout<<"Impossible\n";
		else
			if(exit>0)
				cout<<exit<<' '<<(exit-2*left);
			else
				cout<<(2*right-exit)<<' '<<(-exit);
	}
}
