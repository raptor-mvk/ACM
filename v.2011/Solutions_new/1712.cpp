#include <iostream>

using namespace std;

void rotate(int *grid) {
	int tmp;
	for(int i=0;i<4;i++)
		if(grid[i]<4)
			grid[i]=grid[i]*4+3;
		else
			if(grid[i]<8)
				grid[i]=(grid[i]-4)*4+2;
			else
				if(grid[i]<12)
					grid[i]=(grid[i]-8)*4+1;
				else
					grid[i]=(grid[i]-12)*4;
	for(int i=0;i<3;i++)
		for(int j=0;j<3-i;j++)
			if(grid[j]>grid[j+1]) {
				tmp=grid[j];
				grid[j]=grid[j+1];
				grid[j+1]=tmp;
			}
}

int main() {
	char c,*password;
	int *grid,cur_grid;
	cur_grid=0;
	grid=new int[4];
	password=new char[16];
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			cin>>c;
			if(c=='X')
				grid[cur_grid++]=i*4+j;
		}
		cin.ignore(4,'\n');
	}
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++)
			cin>>password[i*4+j];
		cin.ignore(4,'\n');
	}
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++)
			cout<<password[grid[j]];
			rotate(grid);
	}
}
