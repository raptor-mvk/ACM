#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int MAX_N = 1000;

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	int n, i, j;
	double c[MAX_N], csums[MAX_N], a[MAX_N], an_weights[MAX_N], a0, an, max;
	scanf("%d", &n);
	n -= 2;
	scanf("%lf", &a0);
	an = 0;
	for (i = 0; i < n; i++)
		*(c + i) = 1;
	max = 2 - a0;
	if (n == 1)
	{
		if (a0 > 2.0)
			printf("0.00\n");
		else
			printf("%.2f\n", 2.0 - a0);
		return 0;
	}
	*csums = a0 / 2.0;
	for (i = 1; i < n; i++)
		*(csums + i) = (*(csums + i - 1) - *(c + i - 1)) * (double)i / ((double)i + 1.0);
	*(a + n - 1) = (*(csums + n - 1) - *(c + n - 1) + an / 2.0) / (1.0 - ((double)n - 1.0) / 2.0 /
		(double)n);
	*(an_weights + n - 1) = 0.5 / (1.0 - ((double)n - 1.0) / 2.0 / (double)n);
	if (max < -*(a + n - 1) / *(an_weights + n - 1))
		max = -*(a + n - 1) / *(an_weights + n - 1);
	for (i = n - 2; i > 0; i--)
	{
		*(a + i) = (*(csums + i) - *(c + i) + *(a + i + 1) / 2.0) / (1.0 - (double)i / 2.0 /
			((double)i + 1.0));
		*(an_weights + i) = *(an_weights + i + 1) * 0.5 / (1.0 - (double)i / 2.0 /
			((double)i + 1.0));
		if (max < -*(a + i) / *(an_weights + i))
			max = -*(a + i) / *(an_weights + i);
	}
	*a = *csums - *c + *(a + 1) / 2.0;
	*an_weights = *(an_weights + 1) * 0.5;
	if (max < -*a / *an_weights)
		max = -*a / *an_weights;
	if (max < 0.0)
		max = 0.0;
	printf("%.2f\n", max);
}