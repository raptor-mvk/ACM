// Topic: elementary

#include <stdio.h>
#include <math.h>

int main()
{
  int n;
  scanf("%d", &n);
  if (n == 0) {
    printf("1\n");
  } else {
    printf("%d", (n > 0) ? (1 + n) * n / 2 : -(2 + abs(n)) * (abs(n) - 1) / 2);
  }
  return 0;
}