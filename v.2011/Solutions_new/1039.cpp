#include <iostream>

using namespace std;

void calc_guests(int *next,int *start,int cur,int *count,int *rating,
	int *conv) {
  	int cur_rate_with=0,cur_rate_wo=0;
	  if(!count[cur]) {
     rating[2*cur]=conv[cur];
     rating[2*cur+1]=0;
	  }
  	else {
	    for(int i=0;i<count[cur];i++) {
	      calc_guests(next,start,next[start[cur]+i],count,rating,conv);
  	    cur_rate_with+=rating[2*next[start[cur]+i]+1];
    	  if(rating[2*next[start[cur]+i]+1]>rating[2*next[start[cur]+i]])
      	  cur_rate_wo+=rating[2*next[start[cur]+i]+1];
	      else
					cur_rate_wo+=rating[2*next[start[cur]+i]];
  	  }
    	rating[2*cur]=conv[cur]+cur_rate_with;
	    rating[2*cur+1]=cur_rate_wo;
  	}
}

int main() {
  int n,l,k,cur,root;
  int *next,*start,*conv,*sv,*count,*rating;
  cin>>n;
  next=new int[n];
  start=new int[n];
  conv=new int[n];
  sv=new int[n];
  count=new int[n];
  rating=new int[n*2];
  memset(sv,-1,n*sizeof(int));
  memset(count,0,n*sizeof(int));
  memset(start,0,n*sizeof(int));
  for(int i=0;i<n;i++)
  	cin>>conv[i];
  cin>>l>>k;
  while((l!=0)&&(k!=0)) {
    sv[l-1]=k-1;
    count[k-1]++;
    cin>>l>>k;
  }
  cur=0;
  for(int i=0;i<n;i++) {
    if(sv[i]==-1)
			root=i;
    if(count[i]) {
      start[i]=cur;
      for(int j=0;j<n;j++)
        if(sv[j]==i)
					next[cur++]=j;
    }
  }
  calc_guests(next,start,root,count,rating,conv);
  if(rating[2*root]>rating[2*root+1])
  	cout<<rating[2*root];
  else
  	cout<<rating[2*root+1];
}
