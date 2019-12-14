#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int MAX_QUESTIONS = 10000;
const int HASH_SIZE = 19927;
const char BLACK = 1;
const char WHITE = 2;

int hash_number(int number)
{
	return number % HASH_SIZE;
}

int add_to_hash(int number, int *hash)
{
	int cur_pos;
	cur_pos = hash_number(number);
	while ((*(hash + cur_pos) != 0) && (*(hash + cur_pos) != number))
	{
		if (cur_pos < HASH_SIZE - 1)
			cur_pos++;
		else
			cur_pos = 0;
	}
	if (*(hash + cur_pos) != 0)
		return -1;
	*(hash + cur_pos) = number;
	return cur_pos;
}

void quick_sort(int low, int high, int *a)
{
	int i = low, j = high, x = *(a + (i + j)/2), t;
	while (i<j)
	{
		while (*(a + i) < x) i++;
		while (*(a + j) > x) j--;
		if (i <= j)
		{
			t = *(a + i);
			*(a + i) = *(a + j);
			*(a + j) = t;
			i++;
			j--;
		}
	}
  if (low < j) quick_sort (low, j, a);
	if (high > i) quick_sort(i, high, a);
}

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	int n, i, j, *begins, *ends, *points, pts_count, max_begin, max_end, cur_begin, cur_end;
	char *colors;
	int *hash;
	char c[2];
	char *used;
	scanf("%d", &n);
	hash = new int[HASH_SIZE];
	colors = new char[n + 1];
	begins = new int[n + 1];
	ends = new int[n + 1];
	points = new int[2 * n + 2];
	memset(hash, 0, HASH_SIZE * sizeof(int));
	*points = 0;
	*(points + 1) = 1000000000;
	*(begins + n) = 0;
	*(ends + n) = 1000000000;
	*(colors + n) = WHITE;
	pts_count = 2;
	for (i = n - 1; i >= 0; i--)
	{
		scanf("%d%d%2s", begins + i, ends + i, c);
		*(colors + i) = (*c == 'b') ? BLACK : WHITE;
		if (add_to_hash(*(begins + i), hash) != -1)
			*(points + pts_count++) = *(begins + i);
		if (add_to_hash(*(ends + i), hash) != -1)
			*(points + pts_count++) = *(ends + i);
	}
	used = new char[pts_count - 1];
	memset(used, 0, pts_count - 1);
	quick_sort(0, pts_count - 1, points);
	for (i = 0; i <= n; i++)
		for (j = 0; j < pts_count - 1; j++)
			if (*(used + j) == 0)
			{
				if (*(ends+ i) <= *(points + j))
					break;
				if ((*(begins + i) <= *(points + j)) && (*(ends + i) >= *(points + j + 1)))
					*(used + j) = *(colors + i);
			}
	max_begin = 0;
	max_end = 1;
	cur_begin = 0;
	cur_end = 0;
	for (i = 0; i < pts_count - 1; i++)
		if (*(used + i) == WHITE)
			cur_end = *(points + i + 1);
		else
		{
			if (cur_end - cur_begin > max_end - max_begin)
			{
				max_begin = cur_begin;
				max_end = cur_end;
			}
			cur_begin = *(points + i + 1);
		}
		if (cur_end - cur_begin > max_end - max_begin)
		{
			max_begin = cur_begin;
			max_end = cur_end;
		}
		printf("%d %d\n", max_begin, max_end);
}