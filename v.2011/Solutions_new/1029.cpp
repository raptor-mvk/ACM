#include <iostream>

using namespace std;

const int MIN_FEE=2000000000;

int main() {
	int m,n,*ministry,*cost,j_next,min=MIN_FEE,min_i;
	bool *was;
	cin>>m>>n;
	ministry=new int[m*n];
	cost=new int[m*n];
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			cin>>ministry[i*n+j];
	for(int j=0;j<n;j++)
		cost[(m-1)*n+j]=ministry[(m-1)*n+j];
	for(int i=m-2;i>=0;i--) {
		cost[i*n]=cost[(i+1)*n]+ministry[i*n];
		for(int j=1;j<n;j++)
			cost[i*n+j]=((cost[i*n+j-1]>cost[(i+1)*n+j])?
				cost[(i+1)*n+j]:cost[i*n+j-1])+ministry[i*n+j];
		for(int j=n-1;j>0;j--)
			if(cost[i*n+j]+ministry[i*n+j-1]<cost[i*n+j-1])
				cost[i*n+j-1]=cost[i*n+j]+ministry[i*n+j-1];
	}
	for(int i=0;i<n;i++)
		if(cost[i]<min) {
			min=cost[i];
			min_i=i;
		}
	cout<<(min_i+1)<<' ';
	for(int i=1;i<m-1;) {
		if(cost[i*n+min_i]==cost[(i+1)*n+min_i]+ministry[i*n+min_i]) {
			cout<<(min_i+1)<<' ';
			i++;
		}
		else {
			j_next=min_i;
			while((j_next>0)&&(cost[i*n+j_next]==cost[i*n+j_next-1]+
				ministry[i*n+j_next]))
					j_next--;
			if(cost[i*n+j_next]==cost[(i+1)*n+j_next]+ministry[i*n+j_next]) {
				for(;min_i>=j_next;min_i--)
					cout<<(min_i+1)<<' ';
				i++;
				min_i++;
			}
			else {
				while((min_i<n)&&(cost[i*n+min_i]==cost[i*n+min_i+1]+
					ministry[i*n+min_i]))
						cout<<((min_i++)+1)<<' ';
				cout<<(min_i+1)<<' ';
				i++;
			}
		}
	}
	if(m>1)
		cout<<(min_i+1);
}
