// Topic: data structures

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

const int MAX_QUESTIONS = 5000;
const int HASH_SIZE = 9811;

typedef struct queue queue;

struct queue
{
  int* data;
  int first, length, size;
};

queue* prepare_queue(int new_size)
{
  queue* result;
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

typedef struct list list;

struct list
{
  int data;
  list* next;
};

void add_to_list(list* l, int data)
{
  list* temp;
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

int hash_number(int number)
{
  return number % HASH_SIZE;
}

int add_to_hash(int number, int* hash)
{
  int cur_pos;
  cur_pos = hash_number(number);
  while ((*(hash + cur_pos) != 0) && (*(hash + cur_pos) != number))
  {
    if (cur_pos < HASH_SIZE - 1)
      cur_pos++;
    else
      cur_pos = 0;
  }
  *(hash + cur_pos) = number;
  return cur_pos;
}

int get_from_hash(int number, int* hash)
{
  int cur_pos;
  cur_pos = hash_number(number);
  while (*(hash + cur_pos) != number)
  {
    if (cur_pos < HASH_SIZE - 1)
      cur_pos++;
    else
      cur_pos = 0;
  }
  return cur_pos;
}

int main()
{
  int n, k, i, cur_begin, cur_end, p;
  char answer;
  char c[5];
  int* hash;
  int* group_number;
  int* weight;
  list* next_in_group;
  list* prev_in_group;
  list* temp;
  queue *q;
  q = prepare_queue(MAX_QUESTIONS * 2 + 1);
  hash = malloc(HASH_SIZE * sizeof(int));
  group_number = malloc(HASH_SIZE * sizeof(int));
  weight = malloc(HASH_SIZE * sizeof(int));
  next_in_group = malloc(HASH_SIZE * sizeof(list));
  prev_in_group = malloc(HASH_SIZE * sizeof(list));
  int groups_count;
  scanf("%d", &n);
  while (n != -1) {
    answer = 0;
    groups_count = 0;
    memset(hash, 0, HASH_SIZE * sizeof(int));
    memset(group_number, 0, HASH_SIZE * sizeof(int));
    memset(weight, 0, HASH_SIZE * sizeof(int));
    memset(next_in_group, 0, HASH_SIZE * sizeof(list));
    memset(prev_in_group, 0, HASH_SIZE * sizeof(list));
    scanf("%d", &k);
    for (i = 0; i < k; i++) {
      scanf("%d%d", &cur_begin, &cur_end);
      if (!answer && (cur_end > n)) {
        printf("%d\n", i);
        answer = 1;
      }
      scanf("%4s", &c);
      if (!answer) {
        cur_begin = add_to_hash(cur_begin, hash);
        cur_end = add_to_hash(cur_end + 1, hash);
        if ((*(group_number + cur_begin) == 0) && (*(group_number + cur_end) == 0)) {
          *(group_number + cur_begin) = ++groups_count;
          *(group_number + cur_end) = groups_count;
          add_to_list(next_in_group + cur_begin, cur_end);
          add_to_list(prev_in_group + cur_end, cur_begin);
          *(weight + cur_end) = (*c == 'o') ? 1 : 0;
          continue;
        }
        if ((*(group_number + cur_begin) != 0) && (*(group_number + cur_end) == 0))	{
          *(group_number + cur_end) = *(group_number + cur_begin);
          add_to_list(next_in_group + cur_begin, cur_end);
          add_to_list(prev_in_group + cur_end, cur_begin);
          *(weight + cur_end) = (*(weight + cur_begin) + ((*c == 'o') ? 1 : 0)) % 2;
          continue;
        }
        if ((*(group_number + cur_begin) == 0) && (*(group_number + cur_end) != 0))	{
          *(group_number + cur_begin) = *(group_number + cur_end);
          add_to_list(next_in_group + cur_begin, cur_end);
          add_to_list(prev_in_group + cur_end, cur_begin);
          *(weight + cur_begin) = (*(weight + cur_end) + ((*c == 'o') ? 1 : 0)) % 2;
          continue;
        }
        if ((*(group_number + cur_begin) != 0) && (*(group_number + cur_end) != 0)
          && (*(group_number + cur_begin) != *(group_number + cur_end))) {
            add_to_list(next_in_group + cur_begin, cur_end);
            add_to_list(prev_in_group + cur_end, cur_begin);
            p = ((*(weight + cur_begin) + ((*c == 'o') ? 1 : 0)) % 2 !=
              *(weight + cur_end));
            push_to_queue(q, cur_end);
            while (!is_queue_empty(q)) {
              cur_end = pop_from_queue(q);
              if (*(group_number + cur_end) != *(group_number + cur_begin))	{
                *(group_number + cur_end) = *(group_number + cur_begin);
                if (p == 1) {
                  *(weight + cur_end) = abs(*(weight + cur_end) - 1);
                }
                temp = next_in_group + cur_end;
                while (temp != NULL) {
                  if (temp->data != 0) {
                    push_to_queue(q, temp->data);
                  }
                  temp = temp->next;
                }
                temp = prev_in_group + cur_end;
                while (temp != NULL) {
                  if (temp->data != 0) {
                    push_to_queue(q, temp->data);
                  }
                  temp = temp->next;
                }
              }
            }
            continue;
        }
        if ((*(group_number + cur_begin) != 0) && (*(group_number + cur_end) != 0)
          && (*(group_number + cur_begin) == *(group_number + cur_end))) {
            if ((*(weight + cur_end) + *(weight + cur_begin) + ((*c == 'o')
              ? 1 : 0)) % 2 == 1) {
                printf("%d\n", i);
                answer = 1;
            }
        }
      }
    }
    if (!answer) {
      printf("%d\n", k);
    }
    scanf("%d", &n);
  }
}