#include <iostream>
#include <cmath>

using namespace std;

const int MAX_CITIZENS=10000;
const double EPS=0.00005;

int main() {
  double p,q;
  cin>>p>>q;
  for(int i=1;i<=MAX_CITIZENS;i++) {
    if((int)floor((double)i*p/100.0+EPS)+1<(int)ceil((double)i*q/100.0-EPS)) {
        cout<<i;
        break;
      }
  }
}
