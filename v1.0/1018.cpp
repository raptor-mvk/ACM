#include <stdio.h>
#include <memory.h>

const int MAX_N=100;

void make_tree(int *tree,int *branches,char *count,int prev,int cur,int *id,
              int weight)
{
  int cur_shift=0,cur_id;
  cur_id=*id;
  tree[3*cur_id+2]=weight;
  for(int j=0;j<count[cur];j++)
  {
    if (branches[cur*6+2*j]!=prev)
    {
      tree[3*cur_id+cur_shift++]=++(*id);
      make_tree(tree,branches,count,cur,branches[cur*6+2*j],id,
        branches[cur*6+2*j+1]);
    }
  }
}

int main()
{
  int n,q,a,b,c,apple_sum=0,cur_min;
  int *branches=new int[6*MAX_N];
  int *apple_tree=new int[3*MAX_N];
  char *max_cut=new char[MAX_N];
  int *min_apples=new int[MAX_N*MAX_N];
  char *count=new char[MAX_N];
  memset(apple_tree,0,MAX_N*3*sizeof(int));
  memset(max_cut,0,MAX_N*sizeof(char));
  memset(count,0,MAX_N*sizeof(char));
  memset(min_apples,0,MAX_N*MAX_N*sizeof(int));
  scanf("%d%d",&n,&q);
  for(int i=0;i<n-1;i++)
  {
    scanf("%d%d%d",&a,&b,&c);
    branches[(a-1)*6+2*count[a-1]]=b-1;
    branches[(a-1)*6+2*(count[a-1]++)+1]=c;
    branches[(b-1)*6+2*count[b-1]]=a-1;
    branches[(b-1)*6+2*(count[b-1]++)+1]=c;
    apple_sum+=c;
  }
  a=0;
  make_tree(apple_tree,branches,count,-1,0,&a,0);
  for(int i=n-1;i>=0;i--)
    if (apple_tree[3*i+1]!=0)
    {
      max_cut[i]=max_cut[apple_tree[3*i]]+max_cut[apple_tree[3*i+1]]+2;
      min_apples[i*MAX_N+max_cut[i]]=min_apples[apple_tree[3*i]*MAX_N+
        max_cut[apple_tree[3*i]]]+apple_tree[3*apple_tree[3*i]+2]+
        min_apples[apple_tree[3*i+1]*MAX_N+max_cut[apple_tree[3*i+1]]]+
        apple_tree[3*apple_tree[3*i+1]+2];
      for(int j=1;j<max_cut[i];j++)
      {
        cur_min=min_apples[i*MAX_N+max_cut[i]];
        for(int k=j-max_cut[apple_tree[3*i+1]];k<=max_cut[apple_tree[3*i]];k++)
          if(cur_min>min_apples[apple_tree[3*i]*MAX_N+k]+
            min_apples[apple_tree[3*i+1]*MAX_N+j-k])
            cur_min=min_apples[apple_tree[3*i]*MAX_N+k]+
              min_apples[apple_tree[3*i+1]*MAX_N+j-k];
        if(j>max_cut[apple_tree[3*i]])
          if(cur_min>min_apples[apple_tree[3*i]*MAX_N+
            max_cut[apple_tree[3*i]]]+apple_tree[3*apple_tree[3*i]+2]+
            min_apples[apple_tree[3*i+1]*MAX_N+j-max_cut[apple_tree[3*i]]-1])
              cur_min=min_apples[apple_tree[3*i]*MAX_N+
                max_cut[apple_tree[3*i]]]+apple_tree[3*apple_tree[3*i]+2]+
                min_apples[apple_tree[3*i+1]*MAX_N+j-
                max_cut[apple_tree[3*i]]-1];
        if(j>max_cut[apple_tree[3*i+1]])
          if(cur_min>min_apples[apple_tree[3*i+1]*MAX_N+
            max_cut[apple_tree[3*i+1]]]+apple_tree[3*apple_tree[3*i+1]+2]+
            min_apples[apple_tree[3*i]*MAX_N+j-max_cut[apple_tree[3*i+1]]-1])
              cur_min=min_apples[apple_tree[3*i+1]*MAX_N+
                max_cut[apple_tree[3*i+1]]]+apple_tree[3*apple_tree[3*i+1]+2]+
                min_apples[apple_tree[3*i]*MAX_N+j-
                max_cut[apple_tree[3*i+1]]-1];
        min_apples[i*MAX_N+j]=cur_min;
      }
    }
    else if (apple_tree[3*i]!=0)
    {
      max_cut[i]=max_cut[apple_tree[3*i]]+1;
      for(int j=1;j<max_cut[i];j++)
        min_apples[i*MAX_N+j]=min_apples[apple_tree[3*i]*MAX_N+j];
      min_apples[i*MAX_N+max_cut[i]]=min_apples[apple_tree[3*i]*MAX_N+
        max_cut[apple_tree[3*i]]]+apple_tree[apple_tree[3*i]*3+2];
    }
    else max_cut[i]=0;
  printf("%d",apple_sum-min_apples[n-q-1]);
}
