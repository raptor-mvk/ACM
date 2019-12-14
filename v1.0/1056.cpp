#include <stdio.h>
#include <memory.h>

const int MAX_N=10000;

int mark_tree_down(int *start,int *children,int *parent,int *max_d,
                   int cur,int n)
{
  int cur_max_d=0,cur_end,cur_d;
  if(!start[cur])
  {
    max_d[cur]=0;
    return 0;
  }
  for(cur_d=1;(!start[cur+cur_d])&&(cur+cur_d<n);cur_d++);
  if(cur+cur_d<n) cur_end=start[cur+cur_d];
  else cur_end=n;
  for(int i=start[cur];i<cur_end;i++)
  {
    cur_d=mark_tree_down(start,children,parent,max_d,children[i],n);
    if(cur_d+1>cur_max_d) cur_max_d=cur_d+1;
  }
  max_d[cur]=cur_max_d;
  return cur_max_d;
}

void mark_tree_up(int *start,int *children,int *parent,int *max_d,
                 int *new_max_d,int cur,int n,int cur_d)
{
  int cur_max_d,cur_end,cur_id;
  if(start[cur])
  {
    for(cur_id=1;(!start[cur+cur_id])&&(cur+cur_id<n);cur_id++);
    if(cur+cur_id<n) cur_end=start[cur+cur_id];
    else cur_end=n;
    for(int i=start[cur];i<cur_end;i++)
    {
      cur_max_d=cur_d;
      for(int j=start[cur];j<cur_end;j++)
        if((i!=j)&&(max_d[children[j]]+1>cur_max_d))
          cur_max_d=max_d[children[j]]+1;
      if(max_d[children[i]]>cur_max_d+1)
        new_max_d[children[i]]=max_d[children[i]];
      else
        new_max_d[children[i]]=cur_max_d+1;
      mark_tree_up(start,children,parent,max_d,new_max_d,children[i],
                   n,cur_max_d+1);
    }
  }
}

void quick_sort(int low,int high,int *a,int *b)
{
  int i=low,j=high,x,t;
  x=a[(i+j)/2];
  while(i<j)
  {
    while(a[i]<x) i++;
    while(a[j]>x) j--;
    if (i<=j)
    {
      t=a[i];
      a[i]=a[j];
      a[j]=t;
      t=b[i];
      b[i]=b[j];
      b[j]=t;
      i++;
      j--;
    }
  }
  if(low<j) quick_sort(low,j,a,b);
  if(high>i) quick_sort(i,high,a,b);
}

int main()
{
  int n,center1=1,center2=0,min_max;
  int *parent=new int[MAX_N];
  int *children=new int[MAX_N];
  int *start=new int[MAX_N];
  int *max_d=new int[MAX_N];
  int *new_max_d=new int[MAX_N];
  memset(start,0,MAX_N*sizeof(int));
  scanf("%d",&n);
  parent[0]=-1;
  children[0]=0;
  for(int i=1;i<n;i++)
  {
    scanf("%d",&parent[i]);
    parent[i]--;
    children[i]=i;
  }
  quick_sort(0,n-1,parent,children);
  for(int i=1;i<n;i++)
    if(parent[i]!=parent[i-1]) start[parent[i]]=i;
  mark_tree_down(start,children,parent,max_d,0,n);
  new_max_d[0]=max_d[0];
  mark_tree_up(start,children,parent,max_d,new_max_d,0,n,0);
  min_max=new_max_d[0];
  for(int i=1;i<n;i++)
    if(new_max_d[i]<min_max)
    {
      min_max=new_max_d[i];
      center1=i+1;
      center2=0;
    }
    else if(new_max_d[i]==min_max)
      center2=i+1;
  if(center2) printf("%d %d",center1,center2);
  else printf("%d",center1);
}
