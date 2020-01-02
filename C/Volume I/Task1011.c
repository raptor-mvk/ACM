// Topic: elementary

#include <stdio.h>

const int MAX_CITIZENS = 10000;

int main()
{
  int i;
  double p, q;
  scanf("%lf%lf", &p, &q);
  for (i = 1; i <= MAX_CITIZENS; i++) {
    if (floor((double)i * p / 100.0 + 0.00005) + 0.6 < ceil((double)i * q / 100.0 - 0.00005) - 0.6) {
      printf("%d", i);
      break;
    }
  }
  return 0;
}