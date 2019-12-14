#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int TREE_SIZE = 65536;
const int STEPS_COUNT = 15;
const int INITIAL_MASK = 16384;
const int MAX_N = 15000;

int find_level(int x, int *stars_to_left)
{
	int i, cur_level = 0, cur_step = INITIAL_MASK, cur_position = 1;
	for (i = 0; i < STEPS_COUNT; i++)
	{
		if ((x & cur_step) > 0)
		{
			cur_level += *(stars_to_left + cur_position - 1);
			cur_position <<= 1;
			cur_position++;
			x -= cur_step;
		}
		else
		{
			stars_to_left[cur_position - 1]++;
			cur_position <<= 1;
		}
		cur_step >>= 1;
	}
	cur_level += *(stars_to_left + cur_position - 1);
	stars_to_left[cur_position - 1]++;
	return cur_level;
}

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	int n, i, x, y, stars_to_left[TREE_SIZE], level_stars[MAX_N];
	memset(stars_to_left, 0, TREE_SIZE * sizeof(int));
	memset(level_stars, 0, MAX_N * sizeof(int));
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%d%d", &x, &y);
		level_stars[find_level(x, stars_to_left)]++;
	}
	for (i = 0; i < n; i++)
		printf("%d\n", *(level_stars + i));
}