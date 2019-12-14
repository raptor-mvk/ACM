#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
  int h,H;
  cin>>h>>H;
  if(h*2<H)
    cout<<fixed<<setprecision(6)<<(pow(pow((double)H,2.0/3.0)-
      pow(2.0,2.0/3.0)*pow((double)h,2.0/3.0),1.5)/2);
  else
    cout<<0;
}