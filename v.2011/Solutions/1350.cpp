#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int MAX_STRING_LENGTH = 41;
const int MAX_N = 100;
const int MAX_K = 100;

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

int binary_search(String *list, int first, int last, String item)
{
	int i = (first + last) / 2;
	if (first < last)
	{
		if (*(list + i) == item)
			return i;
		if (*(list + i) > item)
			return binary_search(list, first, --i, item);
		else
			return binary_search(list, ++i, last, item);
	}
	return (*(list + first) == item) ? first : -1;
}

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	int n, k, m, i, j, l, n_safe;
	char *dangerous, *dangerous_count, c;
	String *products, *cur;
	scanf("%d\n", &n);
	products = new String[n];
	cur = new String;
	dangerous = new char[n];
	memset(dangerous, 1, n);
	for (i = 0; i < n; i++)
		scanf("%40[^\n\r]\n", (products + i)->str);
	quick_sort(0, n - 1, products);
	scanf("%d\n", &k);
	dangerous_count = new char[k];
	memset(dangerous_count, 0, k);
	scanf("%d\n", &m);
	n_safe = n - m;
	for (i = 0; i < m; i++)
	{
		scanf("%40[^\n\r]\n", cur->str);
		*(dangerous + binary_search(products, 0, n - 1, *cur)) = 0;
	}
	for (i = 0; i < k; i++)
	{
		scanf("%d\n", &m);
		for (j = 0; j < m; j++)
		{
			scanf("%40[^\n\r]\n", cur->str);
			if (*(dangerous + binary_search(products, 0, n - 1, *cur)))
				dangerous_count[i]++;
		}
	}
	scanf("%d\n", &m);
	for (i = 0; i < k; i++)
	{
		if (*(dangerous_count + i) == 0)
		{
			printf("YES\n");
			continue;
		}
		if (*(dangerous_count + i) <= n_safe - m)
			printf("MAYBE\n");
		if (*(dangerous_count + i) > n_safe - m)
			printf("NO\n");
	}
}