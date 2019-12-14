#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <math.h>

const int MAX_N = 50000;

struct Flag
{
	int x, y, number;
	bool operator< (Flag &right);
	bool operator> (Flag &right);
	Flag &operator= (Flag &right);
};

bool Flag::operator< (Flag &right)
{
	return y < right.y;
}

bool Flag::operator> (Flag &right)
{
	return y > right.y;
}

Flag &Flag::operator= (Flag &right)
{
	x = right.x;
	y = right.y;
	number = right.number;
	return *this;
}

void quick_sort(int low, int high, Flag *a)
{
	int i = low, j = high;
	Flag x, t;
	x = *(a + (i + j) / 2);
	while (i < j)
	{
		while (*(a + i) > x) i++;
		while (*(a + j) < x) j--;
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
	int i, n, way[MAX_N], prev, way_count;
	Flag flags[MAX_N];
	scanf("%d", &n);
	if (n == 1)
	{
		printf("1\n1\n");
		return 0;
	}
	for (i = 0; i < n; i++)
	{
		scanf("%d%d", &((flags + i)->x), &((flags + i)->y));
		(flags+i)->number = i + 1;
	}
	quick_sort(0, n - 1, flags);
	way_count = 1;
	*way = flags->number;
	prev = 0;
	for (i = 1; i < n - 1; i++)
	{
		if (((flags + i)->x - (flags + i + 1)->x) * ((flags + prev)->x - (flags + i)->x) < 0)
		{
			*(way + way_count++) = (flags + i)->number;
			prev = i;
		}
	}
	*(way + way_count++) = (flags + n - 1)->number;
	printf("%d\n", way_count);
	for (i = 0; i < way_count; i++)
		printf("%d ", *(way + i));
	printf("\n");
}