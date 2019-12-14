#include <iostream>

using namespace std;

const int MAX_NEIGHBORS=20;

int get_move(int prev,int start,int *adj,int *count) {
  int move=-1;
  for(int i=0;i<count[start];i++)
    if(adj[start*MAX_NEIGHBORS+i]!=prev)
      if(get_move(start,adj[start*MAX_NEIGHBORS+i],adj,count)==-1)
        if((move==-1)||(move>adj[start*MAX_NEIGHBORS+i]))
          move=adj[start*MAX_NEIGHBORS+i];
  return move;
}

int main() {
  int n,k,beg,end,*adj,*count;
  cin>>n>>k;
  count=new int[n];
  adj=new int[n*MAX_NEIGHBORS];
  memset(count,0,n*sizeof(int));
  for(int i=0;i<n-1;i++) {
		cin>>beg>>end;
    adj[(beg-1)*MAX_NEIGHBORS+count[beg-1]++]=end-1;
    adj[(end-1)*MAX_NEIGHBORS+count[end-1]++]=beg-1;
  }
  n=get_move(-1,k-1,adj,count);
  if(n==-1)
		cout<<"First player loses";
  else
		cout<<"First player wins flying to airport "<<(n+1);
}
