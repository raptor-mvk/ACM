#include <iostream>

using namespace std;

const int LENGTH=9;
const int MAX_SUM=82;
const int DIGITS_COUNT=10;

int main() {
	int sums[MAX_SUM],s;
	cin>>s;
	memset(sums,0,MAX_SUM*sizeof(int));
	for(int i=0;i<DIGITS_COUNT;i++)
		sums[i]++;
	for(int i=1;i<LENGTH;i++)
		for(int j=9*(i+1);j>0;j--)
			for(int k=((DIGITS_COUNT-1>j)?j:(DIGITS_COUNT-1));k>0;k--)
				sums[j]+=sums[j-k];
	sums[1]++;
	cout<<sums[s];
}
