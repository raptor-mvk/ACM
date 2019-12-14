#include <iostream>

using namespace std;

int main() {
  int n;
  cin>>n;
  if(!(n%2))
  	cout<<"yes";
  else {
		cin>>n;
		if(n%2)
			cout<<"yes";
		else
			cout<<"no";
	}
}
