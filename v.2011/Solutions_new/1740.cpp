#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int l,k,h;
	cin>>l>>k>>h;
	cout<<setprecision(5)<<fixed;
	if(!(l%k))
		cout<<(double)(l/k*h)<<' '<<(double)(l/k*h);
	else
		cout<<(double)(l/k*h)<<' '<<(double)(l/k*h+h);
}
