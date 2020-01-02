// Topic: elementary

#include <stdio.h>
#include <math.h>

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

int calc_diff(int *w, int n, int k, int first, int sum, int cur_sum, int cur_min)
{
  int i, temp;
  if (k == 0) {
    return (abs(2 * cur_sum - sum) > cur_min) ? cur_min : abs(2 * cur_sum - sum);
  }
  for (i = 0; i < n - first; i++) {
    cur_sum += *(w + first + i);
    temp = calc_diff(w, n, k - 1, first + i + 1, sum, cur_sum, cur_min);
    cur_sum -= *(w + first + i);
    if (temp < cur_min) {
      cur_min = temp;
    }
  }
  return cur_min;
}

int calc_min_diff(int *w, int min, int max, int sum, int cur_min, int n)
{
  int i;
  for (i = min; i <= max; i++) {
    cur_min = calc_diff(w, n, i, 0, sum, 0, cur_min);
  }
  return cur_min;
}


int main()
{
  int n, i, sum, left, right, min, max, half, cur_min;
  int *w;
  scanf("%d", &n);
  half = n / 2 + n % 2;
  w = malloc(n * sizeof(int));
  sum = 0;
  for (i = 0; i < n; i++) {
    scanf("%d", w + i);
    sum += *(w + i);
  }
  if (n == 1) {
    printf("%d\n", *w);
    return 0;
  }
  quick_sort(0, n - 1, w);
  left = *w;
  i = 0;
  while (left < sum / 2 + sum % 2) {
    left += *(w + ++i);
  }
  max = i;
  if (left == sum - left) {
    printf("0\n");
    return 0;
  }
  right = *(w + n - 1);
  i = n - 1;
  while (right < sum / 2 + sum % 2) {
    right += *(w + --i);
  }
  min = n - i;
  if (right == sum - right) {
    printf("0\n");
    return 0;
  }
  cur_min = (right > left) ? 2 * left - sum : 2 * right - sum;
  if (max - half > half - min) {
    printf("%d\n", calc_min_diff(w, min, half, sum, cur_min, n));
  } else {
    printf("%d\n", calc_min_diff(w, half, max, sum, cur_min, n));
  }
  return 0;
}