#include <stdlib.h>
#include <stdbool.h>

typedef struct queue queue;

struct queue
{
  int *data;
  int first, length, size;
};

queue* prepare_queue(int new_size)
{
  queue *result;
  result = malloc(sizeof(queue));
  result->data = malloc(new_size * sizeof(int));
  result->first = 0;
  result->length = 0;
  result->size = new_size;
  return result;
}
  
bool is_queue_empty(queue* q)
{
  return q->length == 0;
}
  
void push_to_queue(queue* q, int new_elem)
{
  *(q->data + (q->first + (q->length)++) % q->size) = new_elem;
}

long pop_from_queue(queue* q)
{
  long res = *(q->data + (q->first)++);
  (q->length)--;
  if (q->first == q->size) {
    q->first = 0;
  }
  return res;
}

