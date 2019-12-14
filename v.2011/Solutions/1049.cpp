#include <stdio.h>
#include <math.h>
#include <memory.h>

const int MAX_NUMBER=10000;
const int NUMBERS_COUNT=10;

int main()
{
	int primes_count=1,i,j,*primes,n,*dividers,answer;
	primes = new int[MAX_NUMBER];
	*primes = 2;
	for (i=3;i<=MAX_NUMBER;i++)
	{
		*(primes + primes_count)=i;
		for (j=0;j<primes_count;j++)
			if (!(i % *(primes + j)))
			{
				*(primes + primes_count)=0;
				break;
			}
		if (*(primes + primes_count)) primes_count++;
	}
	dividers = new int[primes_count];
	memset(dividers,0,primes_count*sizeof(int));
	for (i=0;i<NUMBERS_COUNT;i++)
	{
		scanf("%d",&n);
		for (j=0;j<primes_count;j++)
		{
			if (n<*(primes + j)) break;
			while (!(n % *(primes + j)))
			{
				n /= *(primes + j);
				dividers[j]++;
			}
		}
	}
	answer=1;
	for (i=0;i<primes_count;i++)
		answer=(answer * (*(dividers + i) + 1)) % 10;
	printf("%d\n",answer);
}