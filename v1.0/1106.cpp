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

int main()
{
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif
	int n, i, j, cur, count=0;
	bool *friends;
	char *groups;
	Queue *q;
	scanf("%d",&n);
	friends = new bool[n*n];
	groups = new char[n];
	q = new Queue(n);
	memset(friends,false,sizeof(bool)*n*n);
	memset(groups,-1,sizeof(char)*n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&cur);
		if (!cur)
		{
			printf("0");
			return 0;
		}
		while (cur!=0)
		{
			*(friends + i * n + cur - 1) = true;
			scanf("%d",&cur);
		}
	}
	for(i=0;i<n;i++)
		if (*(groups+i)==-1)
		{
			q->add(i);
			*(groups+i)=0;
			count++;
			while (!q->is_empty())
			{
				cur=q->get();
				for(j=0;j<n;j++)
					if (*(friends + cur * n + j) && (*(groups + j)==-1))
					{
						q->add(j);
						*(groups+j)=(*(groups+cur) + 1) % 2;
						if (!*(groups+j)) count++;
					}
			}
		}
	printf("%d\n",count);
	for(i=0;i<n;i++)
		if (!*(groups + i)) printf("%d ", i + 1);
}