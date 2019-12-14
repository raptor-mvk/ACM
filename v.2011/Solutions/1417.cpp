#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int BET_SIZE = 20;

void gauss_forward (double *a, int n)
{
	int i, j, k;
	double cur_multiplier;
	for (i = 0; i < n; i++)
	{
		cur_multiplier = 1.0 / *(a + i * (n + 1) + i);
		for (j = 0; j <= n; j++)
			*(a + i * (n + 1) + j) *= cur_multiplier;
		for (j = i + 1; j < n; j++)
		{
			cur_multiplier = *(a + j * (n + 1) + i);
			for (k = i; k <= n; k++)
				*(a + j * (n + 1) + k) -= cur_multiplier * *(a + i * (n + 1) + k);
		}
	}
}

void gauss_backward (double *a, int n)
{
	int i, j ,k;
	double cur_multiplier;
	for (i = n - 1; i > 0; i--)
		for (j = i - 1; j >= 0; j--)
		{
			cur_multiplier = *(a + j * (n + 1) + i);
			for (k = i; k <= n; k++)
				*(a + j * (n + 1) + k) -= cur_multiplier * *(a + i * (n + 1) + k);
		}
}

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	double *a;
	int n, i, j;
	scanf("%d", &n);
	a = new double[(n + 2) * (n + 1)];
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			scanf("%lf", a + i * (n + 2) + j);
			*(a + i * (n + 2) + j) -= BET_SIZE;
		}
	for (i = 0; i < n; i++)
	{
		*(a + i * (n + 2) + n) = -1;
		*(a + i * (n + 2) + n + 1) = 0;
	}
	for (i = 0; i < n; i++)
		*(a + n * (n + 2) + i) = 1;
	*(a + n * (n + 2) + n) = 0;
	*(a + n * (n + 2) + n + 1) = 1;
	gauss_forward(a, n + 1);
	gauss_backward(a, n + 1);
	for (i = 0; i < n; i++)
		printf("%.5f\n", *(a + i * (n + 2) + n + 1));
}