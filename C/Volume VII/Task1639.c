// Topic: elementary

#include <stdio.h>

int main()
{
  int m, n;
  scanf("%d%d", &m, &n);
  if (((m & 1) == 0) || ((n & 1) == 0)) {
    printf("[:=[first]");
  } else {
    printf("[second]=:]\n");
  }
}