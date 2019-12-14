#include <iostream>
#include <cmath>

using namespace std;

const double EPS=0.0000001;

int main() {
  int n,k;
  double t;
  cin>>n;
  for(int i=0;i<n;i++) {
    cin>>k;
    t=sqrt(8.0*(double)k-7.0);
    if(abs(t-floor(t+0.5))>EPS)
      cout<<"0 ";
    else
      cout<<"1 ";
  }
}
