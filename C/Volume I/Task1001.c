// Topic: elementary

#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <math.h>

void calc_sqrt()
{
  long long a;
  if (scanf("%I64d ", &a)!=EOF) {
    calc_sqrt();
    printf("%.4f\n", sqrt((double)a));
  }
}

int main()
{
  calc_sqrt();
  return 0;
}