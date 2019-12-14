#include <stdio.h>
#include <math.h>

const int MAX_N = 10000;
const double PI = acos(-1.0);

void quick_sort(int low, int high, double *a, int *b)
{
  int i = low, j = high, t2;
  double x, t;
  x = *(a + (i + j) / 2);
  while (i < j)
  {
    while (*(a + i) < x) i++;
    while (*(a + j) > x) j--;
    if (i <= j)
    {
      t = *(a + i);
      *(a + i) = *(a + j);
      *(a + j) = t;
      t2 = *(b + i);
      *(b + i) = *(b + j);
      *(b + j) = t2;
      i++;
      j--;
    }
  }
  if (low < j) quick_sort (low, j, a, b);
  if (high > i) quick_sort(i, high, a, b);
}
int main()
{
  int x[MAX_N],y[MAX_N],number[MAX_N];
  double angle[MAX_N];
  int n;
  scanf("%d",&n);
  for(int i=0;i<n;i++)
  {
    scanf("%d%d",&x[i],&y[i]);
    number[i]=i+1;
  }
  angle[0]=0;
  for(int i=1;i<n;i++)
    if(x[i]>x[0]) angle[i]=atan((double)(y[i]-y[0])/(double)(x[i]-x[0]));
    else angle[i]=PI+atan((double)(y[i]-y[0])/(double)(x[i]-x[0]));
  quick_sort(0,n-1,angle,number);
  for(int i=0;i<n;i++)
    if(i%2) printf("%d\n",number[i]);
    else printf("%d ",number[i]);
}