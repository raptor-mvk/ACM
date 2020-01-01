// Topic: elementary

#include <stdio.h>

const int MAX_LENGTH = 3;

int main()
{
  int n, i;
  char c[MAX_LENGTH], to_side1, to_side2, min, max;
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%3s", c);
    to_side1 = ((*c - 'a') > ('h' - *c)) ? ('h' - *c) : (*c - 'a');
    to_side2 = ((*(c + 1) - '1') > ('8' - *(c + 1))) ? ('8' - *(c + 1)) : (*(c + 1) - '1');
    min = (to_side1 > to_side2) ? to_side2 : to_side1;
    max = (to_side1 > to_side2) ? to_side1 : to_side2;
    if (min > 1) {
      printf("8\n");
    }
    if ((max > 1) && (min == 1)) {
      printf("6\n");
    }
    if ((max > 1) && (min == 0) || (max == 1) && (min == 1)) {
      printf("4\n");
    }
    if ((max == 1) && (min == 0)) {
      printf("3\n");
    }
    if (max == 0) {
      printf("2\n");
    }
  }
}