#include <iostream>

using namespace std;

int main() {
  int n,a,b;
  cin>>n>>a>>b;
  cout<<(a/b-1)<<' ';
  for(int i=1;i<n;i++) {
    a=b;
    cin>>b;
    cout<<(a/b-1)<<' ';
  }
}