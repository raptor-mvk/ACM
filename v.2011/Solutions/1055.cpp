#include <stdio.h>
#include <memory.h>

const int MAX_N=50000;
const int MAX_PRIMES=5200;

void find_primes(int *primes, int *primes_count, int n)
{
  int cur, i;
  char is_prime;
  cur = *(primes + *primes_count - 1) + 2;
  while (*primes_count < n)
  {
    is_prime = 1;
    for (i = 1; i < *primes_count; i++)
    {
      if (*(primes + i) * *(primes + i) > cur)
        break;
      if (cur % *(primes + i) == 0)
      {
        is_prime = 0;
        break;
      }
    }
    if (is_prime)
      primes[(*primes_count)++] = cur;
    cur += 2;
  }
}

int main()
{
  int n,m,primes_count,cur,count=0;
  int *primes=new int[MAX_PRIMES];
  int *c_divisors=new int[MAX_PRIMES];
  memset(c_divisors,0,MAX_PRIMES*sizeof(int));
  scanf("%d%d",&n,&m);
  primes[0]=2;
  primes[1]=3;
  primes_count=2;
  find_primes(primes,&primes_count,MAX_PRIMES);
  for(int i=m;i<n;i++)
  {
    cur=i+1;
    for(int j=0;j<primes_count;j++)
      if (cur==1) break;
      else
        while(!(cur%primes[j]))
        {
          cur/=primes[j];
          c_divisors[j]++;
        }
  }
  for(int i=0;i<n-m;i++)
  {
    cur=i+1;
    for(int j=0;j<primes_count;j++)
      if (cur==1) break;
      else
        while(!(cur%primes[j]))
        {
          cur/=primes[j];
          c_divisors[j]--;
        }
  }
  for(int j=0;j<primes_count;j++)
    if(c_divisors[j]) count++;
  printf("%d",count);
}
