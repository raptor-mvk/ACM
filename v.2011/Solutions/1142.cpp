#include <stdio.h>

const int MAX_N=10;

int fact(int k)
{
  if (k<=1) return 1;
  return k*fact(k-1);
}

int calc_c(int n, int k)
{
    int result=1;
    for(int i=1;i<=k;i++)
    {
      result*=(n-i+1);
      result/=i;
    }
    return result;
}

int calc_distributions_count(int n, int k)
{
  int result=0;
  if(k<=0) return 0;
  if(k==1) return 1;
  for(int i=1;i<=n-k+1;i++)
    result+=calc_distributions_count(n-i,k-1)*calc_c(n,i);
  return result;
}

int calc_groupings_count(int n)
{
  int result=0;
  for(int i=1;i<=n;i++)
    result+=calc_distributions_count(n,i);
  return result;
}

int main()
{
  int n, values[MAX_N];
  for(int i=0;i<MAX_N;i++)
    values[i]=calc_groupings_count(i+1);
  scanf("%d",&n);
  while(n!=-1)
  {
    printf("%d\n",values[n-1]);
    scanf("%d",&n);
  }
}
