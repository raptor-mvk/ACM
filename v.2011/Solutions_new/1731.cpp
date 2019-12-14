#include <iostream>

using namespace std;

int main() {
  int m,n;
  cin>>n>>m;
  for(int i=1;i<=n;i++)
    cout<<i<<' ';
  cout<<'\n';
  for(int i=1;i<=m;i++)
    cout<<(i*(n+1))<<' ';
}
