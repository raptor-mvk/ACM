#include <stdio.h>

const int MAX_N=500;

void quick_sort(int low,int high,int *seg_num,int *seg_len)
{
  int i = low, j = high, x, t;
  x = *(seg_len + (i + j) / 2);
  while (i < j)
  {
    while (*(seg_len + i) > x) i++;
    while (*(seg_len + j) < x) j--;
    if (i <= j)
    {
      t = *(seg_len + i);
      *(seg_len + i) = *(seg_len + j);
      *(seg_len + j) = t;
      t = *(seg_num + i);
      *(seg_num + i) = *(seg_num + j);
      *(seg_num + j) = t;
      i++;
      j--;
    }
  }
  if (low < j) quick_sort (low,j,seg_num,seg_len);
  if (high > i) quick_sort(i,high,seg_num,seg_len);
}

int main()
{
  int n,cur_max,cur_prev;
  int *segments=new int[MAX_N*2];
  int *seg_len=new int[MAX_N];
  int *seg_num=new int[MAX_N];
  int *seq_len=new int[MAX_N];
  int *seq_prev=new int[MAX_N];
  scanf("%d",&n);
  for(int i=0;i<n;i++)
  {
    scanf("%d%d",&segments[2*i],&segments[2*i+1]);
    seg_len[i]=segments[2*i+1]-segments[2*i];
    seg_num[i]=i;
  }
  quick_sort(0,n-1,seg_num,seg_len);
  seq_len[0]=1;
  seq_prev[0]=-1;
  for(int i=1;i<n;i++)
  {
    cur_max=1;
    cur_prev=-1;
    for(int j=0;j<i;j++)
      if((segments[2*seg_num[j]]<segments[2*seg_num[i]])&&
        (segments[2*seg_num[i]+1]<segments[2*seg_num[j]+1])&&
        (cur_max<seq_len[j]+1))
        {
          cur_max=seq_len[j]+1;
          cur_prev=j;
        }
    seq_len[i]=cur_max;
    seq_prev[i]=cur_prev;
  }
  cur_max=seq_len[0];
  cur_prev=0;
  for(int i=1;i<n;i++)
    if(cur_max<seq_len[i])
    {
      cur_max=seq_len[i];
      cur_prev=i;
    }
  printf("%d\n",cur_max);
  while(cur_prev>-1)
  {
    printf("%d ",seg_num[cur_prev]+1);
    cur_prev=seq_prev[cur_prev];
  }
}
