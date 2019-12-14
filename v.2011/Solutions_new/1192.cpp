#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI = 3.1415926536;
const double G = 10.0;
const double EPS = 0.00001;
const double GRAD = 180.0;

int main() {
	double v,a,k,vx,vy,dist=0.0;
	cin>>v>>a>>k;
	vx=v*cos(a*PI/GRAD);
	vy=v*sin(a*PI/GRAD);
	while(vx>EPS)	{
		dist+=vx*2.0*vy/G;
		vx/=sqrt(k);
		vy/=sqrt(k);
	}
	cout<<setprecision(2)<<fixed<<dist;
}
