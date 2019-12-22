// Topic: elementary

#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

int main()
{
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  printf("%d\n", n * a * b * 2);
}