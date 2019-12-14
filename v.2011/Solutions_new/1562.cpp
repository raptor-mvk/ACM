#include <iostream>
#include <iomanip>

using namespace std;

const double PI=3.1415926536;

double calc_func(double x,double a,double b) {
	return PI*a*a*x*(1.0-x*x/b/b/3.0);
}

int main() {
	int n;
	double a,b;
	cin>>a>>b>>n;
	for(int i=0;i<n;i++)
		cout<<setprecision(6)<<fixed<<((calc_func(2*b*(i+1)/n-b,a,b)-
			calc_func(2*b*i/n-b,a,b))/8.0)<<'\n';
}