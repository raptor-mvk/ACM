#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  int n,k,sum=0;
  cin>>n;
  for(int i=0;i<n;i++) {
    cin>>k;
    sum+=k;
  }
  cout<<fixed<<setprecision(6)<<((double)sum/(double)n);
}
