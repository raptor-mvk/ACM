#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <string.h>
#include <memory.h>

const int MAX_N = 1024;
const int MAX_STRING_LENGTH = 31;

struct String
{
	char *str;
	String();
	bool operator<(String &right);
	bool operator>(String &right);
	bool operator==(String &right);
	String &operator=(String &right);
};

String::String()
{
	str = new char[MAX_STRING_LENGTH];
	*str = 0;
}

bool String::operator<(String &right)
{
	int i = 0;
	while ((*(str + i) != 0) && (*(right.str + i) != 0))
	{
		if (*(str + i) < *(right.str + i))
			return true;
		if (*(str + i) > *(right.str + i))
			return false;
		i++;
	}
	return *(str + i) < *(right.str + i);
}

bool String::operator>(String &right)
{
	int i = 0;
	while ((*(str + i) != 0) && (*(right.str + i) != 0))
	{
		if (*(str + i) > *(right.str + i))
			return true;
		if (*(str + i) < *(right.str + i))
			return false;
		i++;
	}
	return *(str + i) > *(right.str + i);
}

bool String::operator==(String &right)
{
	int i = 0;
	while ((*(str + i) != 0) && (*(right.str + i) != 0))
	{
		if (*(str + i) != *(right.str + i))
			return false;
		i++;
	}
	return *(str + i) == *(right.str + i);
}

String &String::operator=(String &right)
{
	int i = 0;
	while (*(right.str + i) != 0)
	{
		*(str + i) = *(right.str + i);
		i++;
	}
	*(str + i) = 0;
	return *this;
}

void quick_sort(int low, int high, String *a)
{
	int i = low, j = high;
	String x, t;
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
	int n, i, max, cur;
	String prefectures[MAX_N], name, prev;
	scanf("%d", &n);
	for (i = 0; i < (1 << n); i++)
		scanf("%30s %30s", name.str, (prefectures + i)->str);
	quick_sort(0, (1 << n) - 1, prefectures);
	max = 1;
	cur = 1;
	prev = *prefectures;
	for (i = 1; i < (1 << n); i++)
		if (*(prefectures + i) == prev)
			cur++;
		else
		{
			if (cur > max)
				max = cur;
			cur = 1;
			prev = *(prefectures + i);
		}
	if (cur > max)
		max = cur;
	i = 1;
	cur = 0;
	while (i < max)
	{
		i <<= 1;
		cur++;
	}
	printf("%d\n", n - cur);
}