#include <iostream>

using namespace std;

bool put_queen(char pos_x,char pos_y,char *bad,int n) {
  char cur_x,cur_y;
  if(!bad[pos_x*n+pos_y]) {
    bad[pos_x*n+pos_y]=-1;
    cur_x=-1;
    cur_y=-1;
    while((pos_x+cur_x>=0)&&(pos_y+cur_y>=0))
      bad[(pos_x+cur_x--)*n+pos_y+cur_y--]++;
    cur_x=1;
    cur_y=-1;
    while((pos_x+cur_x<n)&&(pos_y+cur_y>=0))
      bad[(pos_x+cur_x++)*n+pos_y+cur_y--]++;
    cur_x=-1;
    cur_y=1;
    while((pos_x+cur_x>=0)&&(pos_y+cur_y<n))
      bad[(pos_x+cur_x--)*n+pos_y+cur_y++]++;
    cur_x=1;
    cur_y=1;
    while((pos_x+cur_x<n)&&(pos_y+cur_y<n))
      bad[(pos_x+cur_x++)*n+pos_y+cur_y++]++;
    return true;
  }
  else
		return false;
}

void remove_queen(char pos_x,char pos_y,char *bad,int n) {
  char cur_x,cur_y;
  bad[pos_x*n+pos_y]=0;
  cur_x=-1;
  cur_y=-1;
  while((pos_x+cur_x>=0)&&(pos_y+cur_y>=0))
    bad[(pos_x+cur_x--)*n+pos_y+cur_y--]--;
  cur_x=1;
  cur_y=-1;
  while((pos_x+cur_x<n)&&(pos_y+cur_y>=0))
    bad[(pos_x+cur_x++)*n+pos_y+cur_y--]--;
  cur_x=-1;
  cur_y=1;
  while((pos_x+cur_x>=0)&&(pos_y+cur_y<n))
    bad[(pos_x+cur_x--)*n+pos_y+cur_y++]--;
  cur_x=1;
  cur_y=1;
  while((pos_x+cur_x<n)&&(pos_y+cur_y<n))
    bad[(pos_x+cur_x++)*n+pos_y+cur_y++]--;
}

int main() {
  int n,count=0;
  char *bad;
  int *pos_x;
  int *pos_y;
  cin>>n;
	bad=new char[n*n];
	pos_x=new int[n];
	pos_y=new int[n];
  memset(bad,0,n*n*sizeof(char));
  for(int i=0;i<n;i++) {
		cin>>pos_x[i]>>pos_y[i];
    put_queen(--pos_x[i],--pos_y[i],bad,n);
  }
  for(int i=0;i<n;i++) {
    remove_queen(pos_x[i],pos_y[i],bad,n);
    for(int j=i+1;j<n;j++) {
      remove_queen(pos_x[j],pos_y[j],bad,n);
      for(int k=j+1;k<n;k++) {
        remove_queen(pos_x[k],pos_y[k],bad,n);
        if(put_queen(pos_x[j],pos_y[i],bad,n)) {
          if(put_queen(pos_x[k],pos_y[j],bad,n)) {
            if(put_queen(pos_x[i],pos_y[k],bad,n)) {
              count++;
              remove_queen(pos_x[j],pos_y[i],bad,n);
              remove_queen(pos_x[k],pos_y[j],bad,n);
              remove_queen(pos_x[i],pos_y[k],bad,n);
            }
            else {
              remove_queen(pos_x[j],pos_y[i],bad,n);
              remove_queen(pos_x[k],pos_y[j],bad,n);
            }
          }
          else
            remove_queen(pos_x[j],pos_y[i],bad,n);
        }
        if(put_queen(pos_x[k],pos_y[i],bad,n)) {
          if(put_queen(pos_x[i],pos_y[j],bad,n)) {
            if(put_queen(pos_x[j],pos_y[k],bad,n)) {
              count++;
              remove_queen(pos_x[k],pos_y[i],bad,n);
              remove_queen(pos_x[i],pos_y[j],bad,n);
              remove_queen(pos_x[j],pos_y[k],bad,n);
            }
            else {
              remove_queen(pos_x[k],pos_y[i],bad,n);
              remove_queen(pos_x[i],pos_y[j],bad,n);
            }
          }
          else
            remove_queen(pos_x[k],pos_y[i],bad,n);
        }
        put_queen(pos_x[k],pos_y[k],bad,n);
      }
      put_queen(pos_x[j],pos_y[j],bad,n);
    }
    put_queen(pos_x[i],pos_y[i],bad,n);
  }
  cout<<count;
}
