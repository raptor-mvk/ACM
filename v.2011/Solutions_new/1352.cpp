#include <iostream>

using namespace std;

const int MAX_N=38;
const int MERSENNE[MAX_N]={2,3,5,7,13,17,19,31,61,89,107,127,521,607,1279,2203,
                           2281,3217,4253,4423,9689,9941,11213,19937,21701,
                           23209,44497,86243,110503,132049,216091,756839,
                           859433,1257787,1398269,2976221,3021377,6972593};

int main() {
  int k,n;
  cin>>n;
  for(int i=0;i<n;i++) {
    cin>>k;
    cout<<MERSENNE[k-1]<<'\n';
  }
}
