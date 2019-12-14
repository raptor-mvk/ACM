#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <string.h>
#include <memory.h>

const int TEXT_LENGTH = 10001;

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	int errors = 0, sentence = 1, i, in_word;
	char c[TEXT_LENGTH];
	while (scanf("%s", c) != EOF)
	{
		i = 0;
		in_word = 0;
		while (*(c + i) != 0)
		{
			while ((sentence == 1) && (*(c + i) != 0))
				if ((*(c + i) >= 'a') && (*(c + i) <= 'z'))
				{
					sentence = 0;
					in_word = 1;
					i++;
					errors++;
				}
				else if ((*(c + i) >= 'A') && (*(c + i) <= 'Z'))
				{
					sentence = 0;
					in_word = 1;
					i++;
				}
				else i++;
			if (*(c + i) == 0)
				break;
			if (in_word == 1)
				if ((*(c + i) >= 'A') && (*(c + i) <= 'Z'))
				{
					i++;
					errors++;
				}
				else if ((*(c + i) >= 'a') && (*(c + i) <= 'z'))
					i++;
				else if ((*(c + i) == '!') || (*(c + i) == '.') || (*(c + i) == '?'))
				{
					sentence = 1;
					in_word = 0;
					i++;
				}
				else
				{
					in_word = 0;
					i++;
				}
			else
				if (((*(c + i) >= 'A') && (*(c + i) <= 'Z')) || ((*(c + i) >= 'a') && (*(c + i) <= 'z')))
				{
					in_word = 1;
					i++;
				}
				else if ((*(c + i) == '!') || (*(c + i) == '.') || (*(c + i) == '?'))
				{
					sentence = 1;
					i++;
				}
				else
					i++;
		}
	}
	printf("%d\n", errors);
}