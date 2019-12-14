#include <iostream>

using namespace std;

int main() {
  int *horses,*stables,*new_stable;
  int n,k,cur,next,min,cur_count,groups_count=0;
  cin>>n>>k>>cur;
  horses=new int[n];
  stables=new int[n*n];
  new_stable=new int[n*n];
  memset(stables,0,n*n*sizeof(int));
  memset(new_stable,0,n*n*sizeof(int));
  cur_count=1;
  for(int i=1;i<n;i++) {
		cin>>next;
    if(cur==next)
			cur_count++;
    else {
      cur=next;
      horses[groups_count++]=cur_count;
      cur_count=1;
    }
  }
  horses[groups_count++]=cur_count;
  for(int i=0;i<groups_count;i++) {
    cur=0;
    next=0;
    for(int j=i;j<groups_count;j++) {
      if(j%2)
				cur+=horses[j];
      else
				next+=horses[j];
      new_stable[i*n+j]=cur*next;
    }
  }
  for(int i=0;i<groups_count;i++)
    stables[i*n]=new_stable[i];
  for(int i=1;i<k;i++)
    for(int j=i+1;j<groups_count;j++) {
      min=stables[(groups_count-1)*n];
      for(int l=i-1;l<j;l++)
        if(min>stables[l*n+i-1]+new_stable[(l+1)*n+j])
          min=stables[l*n+i-1]+new_stable[(l+1)*n+j];
      stables[j*n+i]=min;
    }
  cout<<stables[(groups_count-1)*n+k-1];
}
