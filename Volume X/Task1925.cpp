/*
  http://acm.timus.ru/problem.aspx?space=1&num=1925
  #elementary
*/

#include <iostream>

using namespace std;

int main() {
	int n,k,b,g=0,temp;
	cin>>n>>k;
	b=k;
	for(int i=0;i<n;i++) {
		cin>>temp;
		b+=temp;
		cin>>temp;
		g+=temp;
	}
	if(b-g>=2*(n+1))
		cout<<(b-g-2*(n+1));
	else
		cout<<"Big Bang!";
}
