#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <math.h>

const int BEG_YEAR = 1600;
const int BEG_SHIFT = 6;
const int MONTHS_COUNT = 12;
const int MONTHS_SHIFT[MONTHS_COUNT + 1] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
const int MAX_WEEKS = 6;
const int DAYS_IN_WEEK = 7;

int main()
{
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif
	int i, j, day, month, year, cur_shift;
	char bracketed = 0, february_shift, calendar[MAX_WEEKS * DAYS_IN_WEEK], days_count[DAYS_IN_WEEK];
	scanf("%d%d%d", &day, &month, &year);
	if (year == BEG_YEAR)
	{
		cur_shift = BEG_SHIFT + MONTHS_SHIFT[month - 1] + (month > 2);
		february_shift = month == 2;
	}
	else
	{
		cur_shift = BEG_SHIFT + (year - BEG_YEAR) * 365 + (year - BEG_YEAR - 1) / 4 - (year - BEG_YEAR - 1) /
			100 + (year - BEG_YEAR - 1) / 400 + MONTHS_SHIFT[month - 1] + ((month > 2) && (year % 4 == 0) &&
			((year % 100 != 0) || (year % 400 == 0))) + 1;
		february_shift = (month == 2) && (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
	}
	cur_shift %= 7;
	if (cur_shift == 0)
		cur_shift = 7;
	memset(days_count, 0, DAYS_IN_WEEK);
	memset(calendar, 0, MAX_WEEKS * DAYS_IN_WEEK);
	for (i = 0; i < cur_shift - 1; i++)
		*(days_count + i) = 1;
	for (i = 0; i < MONTHS_SHIFT[month] - MONTHS_SHIFT[month - 1] +	february_shift; i++)
		*(calendar + (((i + cur_shift) % 7 == 0) ? 6 : ((i + cur_shift) % 7 - 1)) * MAX_WEEKS +
		days_count[(((i + cur_shift) % 7 == 0) ? 6 : ((i + cur_shift) % 7 - 1))]++) = i + 1;
	for (i = 0; i < DAYS_IN_WEEK; i++)
	{
		switch (i)
		{
		case 0:
			printf("mon");
			break;
		case 1:
			printf("tue");
			break;
		case 2:
			printf("wed");
			break;
		case 3:
			printf("thu");
			break;
		case 4:
			printf("fri");
			break;
		case 5:
			printf("sat");
			break;
		case 6:
			printf("sun");
			break;
		}
		for (j = 0; j < MAX_WEEKS; j++)
		{
			if (j > 0)
				printf(" ");
			if (!*(calendar + (i % DAYS_IN_WEEK) * MAX_WEEKS + j))
			{
				printf("    ");
				if (bracketed)
					bracketed = 0;
			}
			else if (!bracketed && (*(calendar + (i % DAYS_IN_WEEK) * MAX_WEEKS + j) != day))
				printf("%4d", *(calendar + (i % DAYS_IN_WEEK) * MAX_WEEKS + j));
			else if (bracketed)
			{
				printf("%3d", *(calendar + (i % DAYS_IN_WEEK) * MAX_WEEKS + j));
				bracketed = 0;
			}
			else
			{
				printf(" [%2d]", *(calendar + (i % DAYS_IN_WEEK) * MAX_WEEKS + j));
				bracketed = 1;
			}
		}
		if (bracketed)
			bracketed = 0;
		printf("\n");
	}
}