// Topic: elementary

#include <stdio.h>

const int PRIME_DIGITS = 4;
const int DIGITS[4] = {2, 3, 5, 7};

int main()
{
  int n, q, i;
  int *dividers = malloc(PRIME_DIGITS * sizeof(int));
  memset(dividers, 0, PRIME_DIGITS * sizeof(int));
  scanf("%d", &n);
  if (n == 1) {
    printf("1\n");
    return 0;
  }
  if (n == 0) {
    printf("10\n");
    return 0;
  }
  for (i = 0; i < PRIME_DIGITS; i++) {
    while (n % DIGITS[i] == 0) {
      dividers[i]++;
      n /= DIGITS[i];
    }
  }
  if (n > 1) {
    printf("-1\n");
    return 0;
  }
  if (((*(dividers) % 3 == 1) && (*(dividers + 1) % 2 != 1)) || ((*(dividers) % 3 == 2) &&
    (*(dividers + 1) % 2 == 1))) {
      printf("2");
  }
  if ((*(dividers + 1) % 2 == 1) && (*(dividers) % 3 == 0)) {
    printf("3");
  }
  if ((*(dividers) % 3 == 2) && (*(dividers + 1) % 2 != 1)) {
    printf("4");
  }
  for (i = 1; i <= *(dividers + 2); i++) {
    printf("5");
  }
  if ((*(dividers) % 3 != 0) && (*(dividers + 1) % 2 == 1)) {
    printf("6");
  }
  for (i = 1; i <= *(dividers + 3); i++) {
    printf("7");
  }
  for (i = 1; i <= *(dividers) / 3; i++) {
    printf("8");
  }
  for (i = 1; i <= *(dividers + 1) / 2; i++) {
    printf("9");
  }
  printf("\n");
  return 0;
}