#include <stdlib.h>

typedef struct list list;

struct list
{
  int data;
  list* next;
};

void add_to_list(list* l, int data)
{
  list *temp;
  if (l->data == 0) {
    l->data = data;
    return;
  }
  temp = l;
  while (temp->next != 0) {
    temp = temp->next;
  }
  temp->next = malloc(sizeof(list));
  temp->next->data = data;
  temp->next->next = NULL;
}
