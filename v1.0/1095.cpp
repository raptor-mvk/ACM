#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int MODS_COUNT = 6;
const int MOD = 7;
const int MODS[MODS_COUNT] = {1, 3, 2, 6, 4, 5};
const int DIGITS_ALWAYS = 4;
const int MAX_DIGITS = 20;
const int ENDINGS[MOD * MODS_COUNT] = {4123, 2143, 4321, 3412, 1432, 3421, 4213, 30142, 40321,
																				10432, 10342, 30412, 40213, 30421, 300412, 200341,
																				300421, 400312, 300241, 400321, 200143, 3004120,
																				3002140, 1004320, 2003410, 2001430, 1003420, 3004210,
																				20004103, 40002103, 20004301, 10003402, 30001402,
																				20003401, 10004203, 100004023, 100002043, 300004021,
																				400003012, 400001032, 400003021, 200004013};

int main()
{
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif
	int n, i, j, length, cur_mod, printed, zeros_count;
	char used[DIGITS_ALWAYS], number[MAX_DIGITS], c;
	scanf("%d\n", &n);
	for (i = 0; i < n; i++)
	{
		memset(used, 0, DIGITS_ALWAYS);
		cur_mod = 0;
		length = 0;
		printed = 0;
		zeros_count = 0;
		scanf("%20s", &number);
		while ((*(number + length) >= '0') && (*(number + length) <= '9'))
			length++;
		for (j = 0; j < length; j++)
			if ((*(number + j) >= '1') && (*(number + j) <= '4'))
			{
				if (*(used + *(number + j) - '1'))
				{
					printf("%c", *(number + j));
					cur_mod += *(MODS + (length - printed++ - 1) % MODS_COUNT) * (*(number + j) - '0');
				}
				else
					*(used + *(number + j) - '1') = 1;
			}
			else if (*(number + j) != '0')
			{
				printf("%c", *(number + j));
				cur_mod += *(MODS + (length - printed++ - 1) % MODS_COUNT) * (*(number + j) - '0');
			}
			else
				zeros_count++;
		printf("%d", *(ENDINGS + (zeros_count % MODS_COUNT) * MOD + (MOD - cur_mod % MOD) % MOD));
		for (j = 0; j < zeros_count / MODS_COUNT; j++)
			printf("000000");
		printf("\n");
	}
}