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

int search_pair (int *list, int first, int last, int number)
{
  int i = (first + last) / 2;
  if (first < last)	{
    if (*(list + i) + number == MAGIC_NUMBER) {
      return i;
    }
    if (*(list + i) + number < MAGIC_NUMBER) {
      return search_pair(list, first, --i, number);
    }	else {
      return search_pair(list, ++i, last, number);
    }
  }
  return (*(list + first) + number != MAGIC_NUMBER) ? -1 : first;
}

int main()
{
  int n1, n2, i, res;
  int *first_list, *second_list;
  scanf("%d", &n1);
  first_list = malloc(n1 * sizeof(int));
  for (i = 0; i < n1; i++) {
    scanf("%d", first_list + i);
  }
  scanf("%d", &n2);
  second_list = malloc(n2 * sizeof(int));
  for (i = 0; i < n2; i++) {
    scanf("%d", second_list + i);
  }
  for (i = 0; i < n1; i++) {
    res = search_pair(second_list, 0, n2 - 1, *(first_list + i));
    if (res != -1) {
      printf("YES\n");
      break;
    }
  }
  if (res == -1) {
    printf("NO\n");
   }
  return 0;
}