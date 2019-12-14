#include <stdio.h>
#include <memory.h>

const int MAX_N = 10002;

int binary_search(int x, int n, int *a)
{
  int p, q, i, l;
  p = 0;
  q = n-1;
  l = 0;
  while (p <= q)
	{
    i = (p + q) / 2;
    ++l;
    if (*(a+i) == x)
			return l;
    if (x < *(a + i))
      q = i - 1;
    else
      p = i + 1;
  }
	return -1;
}

int main()
{
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif
	int *a, n_int_count=0, l, i, j;
	bool *n_val;
	scanf("%d%d", &i, &l);
	a = new int[MAX_N];
	n_val = new bool[MAX_N];
	memset(n_val,false,sizeof(bool)*MAX_N);
	for (j=0;j<MAX_N-1;j++)
	{
		*(a + j) = j;
		if ((j>=i) && (binary_search(i,j,a)==l))
		{
			*(n_val + j)=true;
			if (!*(n_val + j - 1)) n_int_count++;
		}
	}
	printf("%d\n",n_int_count);
	for (j=1;j<MAX_N;j++)
	{
		if (*(n_val + j) && !*(n_val + j - 1)) printf("%d ",j);
		if (!*(n_val + j + 1) && *(n_val + j)) printf("%d\n",j);
	}
}