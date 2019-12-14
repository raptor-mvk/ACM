#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI=3.1415926;

int main() {
	int n,r;
	double res,side,angle;
	cin>>n>>r;
	if (n>=2*r)
		res=(double)r*(double)r*PI;
	else
		if ((double)n*sqrt(2.0)<2.0*(double)r)
			res=(double)n*(double)n;
		else {
			side=sqrt((double)r*(double)r-(double)n*(double)n/4.0);
			angle=atan(2.0*side/(double)n);
			res=(PI-4.0*angle)*(double)r*(double)r+2.0*side*(double)n;
		}
	cout<<setprecision(3)<<fixed<<res;
}
