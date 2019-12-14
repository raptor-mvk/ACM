#include <iostream>

using namespace std;

int main() {
	char a,b,c;
	cin>>a>>b;
	if((b>='0')&&(b<='9')) {
		cin>>c;
		if(c=='A')
			cout<<"window";
		else {
			if((a=='1')||((a=='2')&&(b=='0'))) {
				if(c=='F')
					cout<<"window";
				else
					cout<<"aisle";
			}
			else {
				if(c=='K')
					cout<<"window";
				else
					if((c=='C')||(c=='D')||(c=='G')||(c=='H'))
						cout<<"aisle";
					else
						cout<<"neither";
			}
		}
	}
	else {
		if(b=='A')
			cout<<"window";
		else {
			if((a=='1')||(a=='2')) {
				if(b=='D')
					cout<<"window";
				else
					cout<<"aisle";
			}
			else {
				if(b=='F')
					cout<<"window";
				else
					cout<<"aisle";
			}
		}
	}
}
