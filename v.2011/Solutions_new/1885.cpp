#include <iostream>
#include <iomanip>

using namespace std;

const double EPS=0.0000001;

int main() {
	double h,t,v,x;
	cin>>h>>t>>v>>x;
	cout<<setprecision(6)<<fixed;
	if(x*t>h+EPS)
		cout<<0<<' ';
	else
		cout<<((h-x*t)/(v-x))<<' ';
	if(x*t<h-EPS)
		cout<<t;
	else
		cout<<(h/x);
}
