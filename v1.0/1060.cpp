#include <stdio.h>
#include <memory.h>

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

const int POSITIONS_COUNT = 65536;
const int MOVES_COUNT = 16;
const int MOVES[MOVES_COUNT] = {51200, 58368, 29184, 12544, 35968, 20032, 10016, 4880,
2248, 1252, 626, 305, 140, 78, 39, 19};
const char BLACK='b';
const char WHITE='w';
const int FINISH1 = 0;
const int FINISH2 = 65535;

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	Queue *q = new Queue(POSITIONS_COUNT);
	int *moves = new int[POSITIONS_COUNT];
	char c;
	int i, cur_position = 0;
	memset(moves, -1, sizeof(int)*POSITIONS_COUNT);
	for (i=0;i<MOVES_COUNT;i++)
	{
		scanf("%c",&c);
		while ((c!=BLACK) && (c!=WHITE)) scanf("%c", &c);
		cur_position = (cur_position << 1) + (c == BLACK);
	}
	q->add(cur_position);
	*(moves + cur_position) = 0;
	while (!q->is_empty())
	{
		cur_position=q->get();
		for(i=0;i<MOVES_COUNT;i++)
		{
			if (*(moves + (cur_position ^ MOVES[i]))==-1)
			{
				q->add(cur_position ^ MOVES[i]);
				*(moves + (cur_position ^ MOVES[i]))=*(moves + cur_position) + 1;
			}
		}
		if ((cur_position == FINISH1) || (cur_position == FINISH2)) break;
	}
	if ((cur_position == FINISH1) || (cur_position == FINISH2))
		printf("%d", *(moves + cur_position));
	else
		printf("Impossible");
}