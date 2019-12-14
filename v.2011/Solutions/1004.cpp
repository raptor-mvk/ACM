#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int MAX_N = 100;
const int MIN_INIT = 5000000;

int dfs(int n, int first, int cur, int *adjacent, char *in_use, int cur_way, int cur_length,
				int cur_min, int *cur_min_length, char *cur_min_sequence)
{
	int i, j;
	if (cur_way >= cur_min)
		return cur_min;
	if ((*(adjacent + cur * MAX_N + first) > 0) && (cur_length > 1) && (cur_way + *(adjacent +
			cur * MAX_N + first) < cur_min))
	{
		cur_min = cur_way + *(adjacent + cur * MAX_N + first);
		for (j = 0; j < n; j++)
			if (*(in_use + j) > 0)
				*(cur_min_sequence + *(in_use + j)) = j + 1;
		*(cur_min_sequence + cur_length) = cur + 1;
		*cur_min_sequence = first + 1;
		*cur_min_length = cur_length + 1;
	}
	for (i = first + 1; i < n; i++)
		if (*(adjacent + cur * MAX_N + i) > 0)
			if (*(in_use + i) == 0)
			{
				*(in_use + i) = cur_length + 1;
				cur_min = dfs(n, first, i, adjacent, in_use, cur_way + *(adjacent + cur * MAX_N + i),
					cur_length + 1, cur_min, cur_min_length, cur_min_sequence);
				*(in_use + i) = 0;
			}
	return cur_min;
}

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	int n, m, i, cur_begin, cur_end, cur_weight, cur_min, cur_min_length;
	int *adjacent;
	char *in_use;
	char *cur_min_sequence;
	adjacent = new int[MAX_N * MAX_N];
	in_use = new char[MAX_N];
	cur_min_sequence = new char[MAX_N];
	scanf("%d%d", &n, &m);
	while (n != -1)
	{
		memset(adjacent, 0, MAX_N * MAX_N * sizeof(int));
		memset(in_use, 0, MAX_N);
		memset(cur_min_sequence, 0, MAX_N);
		cur_min = MIN_INIT;
		cur_min_length = 0;
		for (i = 0; i < m; i++)
		{
			scanf("%d%d%d", &cur_begin, &cur_end, &cur_weight);
			if ((*(adjacent + MAX_N * (cur_begin - 1) + cur_end - 1) == 0) ||
				(*(adjacent + MAX_N * (cur_begin - 1) + cur_end - 1) > cur_weight))
			{
				*(adjacent + MAX_N * (cur_begin - 1) + cur_end - 1) = cur_weight;
				*(adjacent + MAX_N * (cur_end - 1) + cur_begin - 1) = cur_weight;
			}
		}
		for (i = 0; i < n; i++)
		{
			cur_min = dfs(n, i, i, adjacent, in_use, 0, 0, cur_min, &cur_min_length,
				cur_min_sequence);
		}
		if (cur_min == MIN_INIT)
			printf("No solution.\n");
		else
		{
			for (i = 0; i < cur_min_length; i++)
				printf("%d ", *(cur_min_sequence + i));
			printf("\n");
		}
		scanf("%d%d", &n, &m);
	}
}