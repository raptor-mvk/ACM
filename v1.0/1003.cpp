#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int MAX_QUESTIONS = 5000;
const int HASH_SIZE = 9811;

class Queue
{
private:
	int *queue;
	int first, length, size;
public:
	Queue(int new_size);
	~Queue();
	bool is_empty();
	void add(int new_elem);
	int get();
};

Queue::Queue(int new_size)
{
	queue = new int[new_size];
	first = 0;
	length = 0;
	size = new_size;
}

Queue::~Queue()
{
	delete [] queue;
}

bool Queue::is_empty()
{
	return length == 0;
}

void Queue::add(int new_elem)
{
	*(queue + (first + length++) % size) = new_elem;
}

int Queue::get()
{
	int res = *(queue + first++);
	length--;
	if (first == size)
		first = 0;
	return res;
}

struct list
{
	int data;
	list *next;
	void add(int number);
};

void list::add(int number)
{
	list *temp;
	if (data == 0)
	{
		data = number;
		return;
	}
	temp = this;
	while (temp->next != 0)
		temp = temp->next;
	temp->next = new list;
	temp->next->data = number;
	temp->next->next = NULL;
}

int hash_number(int number)
{
	return number % HASH_SIZE;
}

int add_to_hash(int number, int *hash)
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

int get_from_hash(int number, int *hash)
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
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	int n, k, i, cur_begin, cur_end, p;
	char answer;
	char c[5];
	int *hash;
	int *group_number;
	int *weight;
	list *next_in_group;
	list *prev_in_group;
	list *temp;
	Queue *q;
	q = new Queue(MAX_QUESTIONS * 2 + 1);
	hash = new int[HASH_SIZE];
	group_number = new int[HASH_SIZE];
	weight = new int[HASH_SIZE];
	next_in_group = new list[HASH_SIZE];
	prev_in_group = new list[HASH_SIZE];
	int groups_count;
	scanf("%d", &n);
	while (n != -1)
	{
		answer = 0;
		groups_count = 0;
		memset(hash, 0, HASH_SIZE * sizeof(int));
		memset(group_number, 0, HASH_SIZE * sizeof(int));
		memset(weight, 0, HASH_SIZE * sizeof(int));
		memset(next_in_group, 0, HASH_SIZE * sizeof(list));
		memset(prev_in_group, 0, HASH_SIZE * sizeof(list));
		scanf("%d", &k);
		for (i = 0; i < k; i++)
		{
			scanf("%d%d", &cur_begin, &cur_end);
			if (!answer && (cur_end > n))
			{
				printf("%d\n", i);
				answer = 1;
			}
			scanf("%4s", &c);
			if (!answer)
			{
				cur_begin = add_to_hash(cur_begin, hash);
				cur_end = add_to_hash(cur_end + 1, hash);
				if ((*(group_number + cur_begin) == 0) && (*(group_number + cur_end) == 0))
				{
					*(group_number + cur_begin) = ++groups_count;
					*(group_number + cur_end) = groups_count;
					(next_in_group + cur_begin)->add(cur_end);
					(prev_in_group + cur_end)->add(cur_begin);
					*(weight + cur_end) = (*c == 'o') ? 1 : 0;
					continue;
				}
				if ((*(group_number + cur_begin) != 0) && (*(group_number + cur_end) == 0))
				{
					*(group_number + cur_end) = *(group_number + cur_begin);
					(next_in_group + cur_begin)->add(cur_end);
					(prev_in_group + cur_end)->add(cur_begin);
					*(weight + cur_end) = (*(weight + cur_begin) + ((*c == 'o') ? 1 : 0)) % 2;
					continue;
				}
				if ((*(group_number + cur_begin) == 0) && (*(group_number + cur_end) != 0))
				{
					*(group_number + cur_begin) = *(group_number + cur_end);
					(next_in_group + cur_begin)->add(cur_end);
					(prev_in_group + cur_end)->add(cur_begin);
					*(weight + cur_begin) = (*(weight + cur_end) + ((*c == 'o') ? 1 : 0)) % 2;
					continue;
				}
				if ((*(group_number + cur_begin) != 0) && (*(group_number + cur_end) != 0)
					&& (*(group_number + cur_begin) != *(group_number + cur_end)))
				{
					(next_in_group + cur_begin)->add(cur_end);
					(prev_in_group + cur_end)->add(cur_begin);
					p = ((*(weight + cur_begin) + ((*c == 'o') ? 1 : 0)) % 2 != *(weight + cur_end));
					q->add(cur_end);
					while (!q->is_empty())
					{
						cur_end = q->get();
						if (*(group_number + cur_end) != *(group_number + cur_begin))
						{
							*(group_number + cur_end) = *(group_number + cur_begin);
							if (p == 1)
								*(weight + cur_end) = abs(*(weight + cur_end) - 1);
							temp = next_in_group + cur_end;
							while (temp != NULL)
							{
								if (temp->data != 0)
									q->add(temp->data);
								temp = temp->next;
							}
							temp = prev_in_group + cur_end;
							while (temp != NULL)
							{
								if (temp->data != 0)
									q->add(temp->data);
								temp = temp->next;
							}
						}
					}
					continue;
				}
				if ((*(group_number + cur_begin) != 0) && (*(group_number + cur_end) != 0)
					&& (*(group_number + cur_begin) == *(group_number + cur_end)))
				{
					if ((*(weight + cur_end) + *(weight + cur_begin) + ((*c == 'o') ? 1 : 0)) % 2 == 1)
					{
						printf("%d\n", i);
						answer = 1;
					}
				}
			}
		}
		if (!answer)
			printf("%d\n", k);
		scanf("%d", &n);
	}
}