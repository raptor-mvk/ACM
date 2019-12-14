#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <string.h>
#include <memory.h>

const int MAX_LENGTH = 1002;

void insert_digit(char *c, int length, int position, char digit)
{
	for (int i = 0; i < length; i++)
	{
		if (i == position)
			printf("%c", digit);
		printf("%c", *(c + i));
	}
	if (position == length)
		printf("%c", digit);
	printf("\n");
}

void delete_digit(char *c, int length, int position)
{
	for (int i = 0; i < length; i++)
		if (i != position)
			printf("%c", *(c + i));
	printf("\n");
}

int search_one(int *list, int number, int shift)
{
	int cur = number, prev = 0;
	while ((cur >= 0) && (*(list + cur) + cur + shift >= number))
	{
		prev = cur;
		cur -= (*(list + cur) + cur + shift - number > 0) ? *(list + cur) + cur + shift - number : 1;
	}
	return prev;
}

int binary_search(int *list, int first, int last, int number)
{
	int i = (first + last) / 2;
	if (first < last)
	{
		if (*(list + i) == number)
			return binary_search(list, first, i, number);
		if (*(list + i) < number)
			return binary_search(list, first, --i, number);
		else
			return binary_search(list, ++i, last, number);
	}
	return (*(list + first) != number) ? -1 : first;
}

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	int n, i, length, sum, position;
	char c[MAX_LENGTH];
	int ones_after[MAX_LENGTH];
	scanf("%d", &n);
	while (scanf("%1002s", &c) != EOF)
	{
		sum = 0;
		length = strlen(c);
		memset(ones_after, 0, MAX_LENGTH * sizeof(int));
		for (i = length - 1; i >= 0; i--)
		{
			sum += (*(c + i) == '1') * (i + 1);
			*(ones_after + i) = *(ones_after + i + 1) + (*(c + i) == '1');
		}
		if (length == n - 1)
		{
			if (sum % (n + 1) == 0)
				insert_digit(c, length, length, '0');
			else if (n + 1 - sum % (n + 1) <= *ones_after)
			{
				position = binary_search(ones_after, 0, n - 1, n + 1 - sum % (n + 1));
				insert_digit(c, length, position, '0');
			}
			else
			{
				position = search_one(ones_after, n + 1 - sum % (n + 1), 1);
				insert_digit(c, length, position, '1');
			}
		}
		if (length == n)
			if (sum % (n + 1) == 0)
				printf("%s\n", &c);
			else
			{
				*(c + sum % (n + 1) - 1) = '0';
				printf("%s\n", &c);
			}
		if (length == n + 1)
		{
			if (sum % (n + 1) == 0)
				delete_digit(c, length, length - 1);
			else if (sum % (n + 1) <= *(ones_after + 1))
			{
				position = binary_search(ones_after, 0, n, sum % (n + 1));
				delete_digit(c, length, position);
			}
			else
			{
				position = search_one(ones_after, sum % (n + 1), 0);
				delete_digit(c, length, position);
			}
		}
	}
	return 0;
}