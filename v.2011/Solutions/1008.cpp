#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <string.h>
#include <memory.h>

const int MAX_COORD = 12;
const int MAX_LENGTH = 6;

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

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	int a, b, i, j, n;
	char pts[MAX_COORD * MAX_COORD];
	char c[MAX_LENGTH];
	Queue *q_x, *q_y;
	q_x = new Queue(MAX_COORD * MAX_COORD);
	q_y = new Queue(MAX_COORD * MAX_COORD);
	memset(pts, 0, MAX_COORD * MAX_COORD);
	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%5s", &c);
	if ((*c >= '1') && (*c <= '9'))
	{
		n = a;
		printf("%d %s\n", b, c);
		q_x->add(b);
		if (*(c + 1) != 0)
			a = 10;
		else
			a = *c - '0';
		q_y->add(a);
		for (i = 1; i < n; i++)
		{
			scanf("%d%d", &a, &b);
			*(pts + a * MAX_COORD + b) = 1;
		}
		while (!q_x->is_empty())
		{
			memset(c, 0, MAX_LENGTH);
			i = 0;
			a = q_x->get();
			b = q_y->get();
			if (*(pts + (a + 1) * MAX_COORD + b) != 0)
			{
				q_x->add(a + 1);
				q_y->add(b);
				*(c + i++) = 'R';
				*(pts + (a + 1) * MAX_COORD + b) = 0;
			}
			if (*(pts + a * MAX_COORD + b + 1) != 0)
			{
				q_x->add(a);
				q_y->add(b + 1);
				*(c + i++) = 'T';
				*(pts + a * MAX_COORD + b + 1) = 0;
			}
			if (*(pts + (a - 1) * MAX_COORD + b) != 0)
			{
				q_x->add(a - 1);
				q_y->add(b);
				*(c + i++) = 'L';
				*(pts + (a - 1) * MAX_COORD + b) = 0;
			}
			if (*(pts + a * MAX_COORD + b - 1) != 0)
			{
				q_x->add(a);
				q_y->add(b - 1);
				*(c + i++) = 'B';
				*(pts + a * MAX_COORD + b - 1) = 0;
			}
			if (q_x->is_empty())
				*(c + i) = '.';
			else
				*(c + i) = ',';
			printf("%s\n", c);
		}
	}
	else
	{
		n = 1;
		q_x->add(a);
		q_y->add(b);
		*(pts + a * MAX_COORD + b) = 1;
		while (!q_x->is_empty())
		{
			i = 0;
			a = q_x->get();
			b = q_y->get();
			if (*(c + i) == 'R')
			{
				n++;
				i++;
				q_x->add(a + 1);
				q_y->add(b);
				*(pts + (a + 1) * MAX_COORD + b) = 1;
			}
			if (*(c + i) == 'T')
			{
				n++;
				i++;
				q_x->add(a);
				q_y->add(b + 1);
				*(pts + a * MAX_COORD + b + 1) = 1;
			}
			if (*(c + i) == 'L')
			{
				n++;
				i++;
				q_x->add(a - 1);
				q_y->add(b);
				*(pts + (a - 1) * MAX_COORD + b) = 1;
			}
			if (*(c + i) == 'B')
			{
				n++;
				i++;
				q_x->add(a);
				q_y->add(b - 1);
				*(pts + a * MAX_COORD + b - 1) = 1;
			}
			scanf("%5s\n", c);
		}
		printf("%d\n", n);
		for (i = 1; i < MAX_COORD - 1; i++)
			for (j = 1; j < MAX_COORD - 1; j++)
				if (*(pts + i * MAX_COORD + j) != 0)
					printf("%d %d\n", i, j);
	}
	return 0;
}