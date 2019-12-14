#include <iostream>

using namespace std;

int main() {
	int *pos,cur,min;
	pos=new int[4];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++) {
			cin>>cur;
			if(cur==1)
			switch(i*4+j)	{
				case 0:
					pos[0]=0;
					break;
				case 1:
					pos[1]=0;
					break;
				case 2:
					pos[2]=1;
					break;
				case 3:
					pos[0]=1;
					break;
				case 4:
					pos[2]=0;
					break;
				case 5:
					pos[3]=0;
					break;
				case 6:
					pos[3]=1;
					break;
				case 7:
					pos[1]=1;
					break;
				case 8:
					pos[1]=3;
					break;
				case 9:
					pos[3]=3;
					break;
				case 10:
					pos[3]=2;
					break;
				case 11:
					pos[2]=2;
					break;
				case 12:
					pos[0]=3;
					break;
				case 13:
					pos[2]=3;
					break;
				case 14:
					pos[1]=2;
					break;
				case 15:
					pos[0]=2;
					break;
			}
		}
	min=16;
	for(int i=0;i<4;i++) {
		cur=0;
		for(int j=0;j<4;j++)
			if(abs(pos[j]-i)==2)
				cur+=2;
			else
				if(pos[j]!=i)
					cur+=1;
		if(cur<min)
			min=cur;
	}
	cout<<min;				
}
