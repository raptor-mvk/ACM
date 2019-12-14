#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <math.h>

const int MAX_K = 2001;

int main()
{
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif
	int last, cur;
	char number[MAX_K];
	scanf("%s", number);
	last = 0;
	while (*(number + last) != 0)
		last++;
	last--;
	if (last == 0)
	{
		printf("-1\n");
		return 0;
	}
	if ((*(number + last) != '0') && (*(number + last - 1) != '9'))
	{
		number[last]--;
		number[last - 1]++;
		printf("%s\n", number);
	}
	else if ((*(number + last) != '0') && (*(number + last - 1) == '9'))
	{
		cur = last - 1;
		while ((*(number + cur) == '9') && (cur >= 0))
			cur--;
		if (cur < 0)
		{
			printf("-1\n");
			return 0;
		}
		number[cur]++;
		*(number + cur + 1) = *(number + last) - 1;
		*(number + last) = '9';
		printf("%s\n", number);
	}
	else
	{
		cur = last;
		while ((*(number + cur) == '0') && (cur >= 0))
			cur--;
		if (cur < 0)
		{
			printf("-1\n");
			return 0;
		}
		*(number + last) = *(number + cur) - 1;
		*(number + cur--) = '0';
		last--;
		while ((*(number + cur) == '9') && (cur >= 0))
		{
			*(number + last) = *(number + last + 1);
			*(number + last-- + 1) = '9';
			*(number + cur--) = '0';
		}
		if (cur < 0)
		{
			printf("-1\n");
			return 0;
		}
		number[cur]++;
		printf("%s\n", number);
	}
}