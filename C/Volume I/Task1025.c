// Topic: elementary

#include <stdio.h>

const int MAGIC_NUMBER = 10000;

void quick_sort(int low, int high, int *a)
{
  int i = low, j = high, x = *(a + (i + j)/2), t;
  while (i<j) {
    while (*(a + i) < x) {
      i++;
    }
    while (*(a + j) > x) {
      j--;
    }
    if (i <= j) {
      t = *(a + i);
      *(a + i) = *(a + j);
      *(a + j) = t;
      i++;
      j--;
    }
  }
  if (low < j) {
    quick_sort (low, j, a);
  }
  if (high > i) {
    quick_sort(i, high, a);
  }
}

int main()
{
  int *a, k, i, s = 0;
  scanf("%d", &k);
  a = malloc(k * sizeof(int));
  for (i = 0; i < k; i++) {
    scanf("%d", a + i);
  }
  quick_sort(0, k-1, a);
  for (i = 0; i < k/2 + (k % 2 == 1); i++) {
    s += *(a + i) / 2 + (*(a + i) % 2 == 1);
  }
  printf("%d\n", s);
  return 0;
}