#include <iostream>

using namespace std;

int main() {
	int n;
	char c1,c2,to_side1,to_side2,min,max;
	cin>>n;
	cin.ignore(1,'\n');
	for(int i=0;i<n;i++) {
		cin>>c1>>c2;
		cin.ignore(1,'\n');
		to_side1=((c[0]-'a')>('h'-c[0]))?('h'-c[0]):(c[0]-'a');
		to_side2=((c[1]-'1')>('8'-c[1]))?('8'-c[1]):(c[1]-'1');
		min=(to_side1>to_side2)?to_side2:to_side1;
		max=(to_side1>to_side2)?to_side1:to_side2;
		if(min>1)
			cout<<"8\n";
		if((max>1)&&(min==1))
			cout<<"6\n";
		if((max>1)&&(min==0)||(max == 1)&&(min == 1))
			cout<<"4\n";
		if((max == 1)&&(min == 0))
			cout<<"3\n";
		if(max==0)
			cout<<"2\n";
	}
}
