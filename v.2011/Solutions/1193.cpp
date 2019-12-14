#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int MAX_N = 100;

struct Student
{
	int beginning, length, wanted_ending;
	Student(): beginning(0), length(0), wanted_ending(0) {}
	Student(int a, int b, int c): beginning(a), length(b), wanted_ending(c) {}
	bool operator<(Student &right);
	bool operator>(Student &right);
	Student &operator=(Student &right);
};

bool Student::operator<(Student &right)
{
	return beginning < right.beginning;
}

bool Student::operator>(Student &right)
{
	return beginning > right.beginning;
}

Student &Student::operator=(Student &right)
{
	beginning = right.beginning;
	length = right.length;
	wanted_ending = right.wanted_ending;
	return *this;
}

void quick_sort(int low, int high, Student *a)
{
	int i = low, j = high;
	Student x, t;
	x = *(a + (i + j) / 2);
	while (i<j)
	{
		while (*(a + i) < x) i++;
		while (*(a + j) > x) j--;
		if (i <= j)
		{
			t = *(a + i);
			*(a + i) = *(a + j);
			*(a + j) = t;
			i++;
			j--;
		}
	}
  if (low < j) quick_sort (low, j, a);
	if (high > i) quick_sort(i, high, a);
}

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
	int n, i, cur, max_shift, students_left, cur_student, end_of_cur_answer, cur_time;
	Student students_list[MAX_N];
	Queue *q;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%d%d%d", &cur, &max_shift, &students_left);
		*(students_list + i) = Student(cur, max_shift, students_left);
	}
	quick_sort(0, n - 1, students_list);
	max_shift = 0;
	students_left = n;
	cur_student = 0;
	q = new Queue(MAX_N);
	cur_time = students_list->beginning;
	end_of_cur_answer = 0;
	while (students_left > 0)
	{
		if (cur_time == (students_list + cur_student)->beginning)
		{
			if (cur_time > end_of_cur_answer)
			{
				end_of_cur_answer = cur_time + (students_list + cur_student)->length;
				if (max_shift < end_of_cur_answer - (students_list + cur_student)->wanted_ending)
					max_shift = end_of_cur_answer - (students_list + cur_student)->wanted_ending;
				cur_student++;
			}
			else
				q->add(cur_student++);
		}
		if (cur_time == end_of_cur_answer)
		{
			students_left--;
			if (!q->is_empty())
			{
				cur = q->get();
				end_of_cur_answer = cur_time + (students_list + cur)->length;
				if (max_shift < end_of_cur_answer - (students_list + cur)->wanted_ending)
					max_shift = end_of_cur_answer - (students_list + cur)->wanted_ending;
			}
		}
		cur_time++;
	}
	printf("%d\n", max_shift);
}