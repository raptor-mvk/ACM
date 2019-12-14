#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int MAX_N = 10000;
const int MAX_STEPS = 17;

int main()
{
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif
	int n, cur_step, cur_mod, mod_count, cur_pos, i, j, k, order[MAX_N * MAX_STEPS], steps_count;
	char finished, used[MAX_N];
	scanf("%d", &n);
	finished = 1;
	for (i = 0; i < n; i++)
	{
		scanf("%d", order + i);
		if (*(order + i) != i + 1)
			finished = 0;
	}
	if (finished)
	{
		printf("0\n");
		for (i = 0; i < n; i++)
			printf("%d ", *(order + i));
		return 0;
	}
	cur_step = 2;
	while (cur_step < n)
		cur_step <<= 1;
	finished = 0;
	steps_count = 1;
	while (!finished)
	{
		memset(used, 0, MAX_N);
		cur_mod = 1;
		mod_count = 0;
		cur_pos = 0;
		for (j = 0; j < 2; j++)
			for (i = 0; i < n; i++)
				if (!*(used + i) && (*(order + i) % cur_step == cur_mod))
				{
					mod_count++;
					cur_pos++;
					*(used + i) = 1;
					if ((cur_mod > n % cur_step) && (mod_count >= n / cur_step) ||
						(cur_mod <= n % cur_step) && (mod_count > n / cur_step))
					{
						cur_mod++;
						mod_count = 0;
						cur_mod %= cur_step;
					}
				}
		if (cur_pos == n)
			finished = 1;
		else
		{
			cur_step >>= 1;
			steps_count++;
		}
	}
	for (k = 0; k < steps_count; k++)
	{
		cur_pos = 0;
		for (i = 0; i < ((cur_step > n) ? n : cur_step); i++)
			for (j = 0; j < n; j++)
				if (*(order + k * MAX_N + j) % cur_step == (i + 1) % cur_step)
					*(order + (k + 1) * MAX_N + cur_pos++) = *(order + k * MAX_N + j);
		cur_step <<= 1;
	}
	printf("%d\n", steps_count);
	for (i = 0; i <= steps_count; i++)
	{
		for (j = 0; j < n; j++)
			printf("%d ", *(order + i * MAX_N + j));
		printf("\n");
	}
}