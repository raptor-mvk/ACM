#include <iostream>

using namespace std;

int main() {
	int a,b,c,d,e,f,g,sum;
	cin>>a>>b>>c>>d>>e>>f>>g;
	sum=(e==b^c^d)+(f==a^c^d)+(g==a^b^d);
	switch(sum) {
		case 0:
			cout<<a<<' '<<b<<' '<<c<<' '<<(d^1)<<' '<<e<<' '<<f<<' '<<g;
			break;
		case 1:
			if(e==b^c^d)
				cout<<(a^1)<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' '<<f<<' '<<g;
			else
				if(f==a^c^d)
					cout<<a<<' '<<(b^1)<<' '<<c<<' '<<d<<' '<<e<<' '<<f<<' '<<g;
				else
					cout<<a<<' '<<b<<' '<<(c^1)<<' '<<d<<' '<<e<<' '<<f<<' '<<g;
			break;
		case 2:
			if(e!=b^c^d)
				cout<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<(e^1)<<' '<<f<<' '<<g;
			else
				if(f!=a^c^d)
					cout<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' '<<(f^1)<<' '<<g;
				else
					cout<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' '<<f<<' '<<(g^1);
			break;
		case 3:
			cout<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' '<<f<<' '<<g;
			break;
	}
}
