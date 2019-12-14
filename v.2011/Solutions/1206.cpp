#pragma comment(linker, "/STACK:16777216")

#include <stdio.h>
#include <memory.h>
#include <math.h>

const int MAX_LENGTH = 3;
const int HUGE_LENGTH = 100;
const int FOUNDATION = 10;

class Huge
{
private:
	char *number;
	int length;
public:
	Huge();
	~Huge();
	void print();
	int get_digit(int digit_index);
	void sum(Huge *a, Huge *b);
	void mul_byte(Huge *a, char b, int shift);
	void mul(Huge *a, Huge *b);
	void init(int b);
};

Huge::Huge()
{
	number = new char[HUGE_LENGTH];
	length = 0;
}

Huge::~Huge()
{
	delete [] number;
}

int Huge::get_digit(int digit_index)
{
	return (digit_index < length) ? *(number + digit_index) : 0;
}

void Huge::sum(Huge *a, Huge *b)
{
	int max, i;
	char p = 0, temp;
	max = (a->length >= b->length) ? a->length : b->length;
	for (i = 0; i < max; i++)
	{
		temp = a->get_digit(i) + b->get_digit(i) + p;
		*(number + i) = temp % FOUNDATION;
		p = temp / FOUNDATION;
	}
	*(number + max) = p;
	length = max + (p != 0);
}

void Huge::mul(Huge *a, Huge *b)
{
	Huge *temp1, *temp2;
	int i;
	temp1 = new Huge;
	temp2 = new Huge;
	if (b->length == 1)
	{
		this->mul_byte(a, b->get_digit(0), 0);
		return;
	}
	temp1->mul_byte(a, b->get_digit(0), 0);
	temp2->mul_byte(a, b->get_digit(1), 1);
	temp1->sum(temp1, temp2);
	for (i = 2; i < b->length; i++)
	{
		temp2->mul_byte(a, b->get_digit(i), i);
		temp1->sum(temp1, temp2);
	}
	for (i = 0; i < temp1->length; i++)
		*(this->number + i) = *(temp1->number + i);
	this->length = temp1->length;
	delete temp1;
	delete temp2;
}

void Huge::mul_byte(Huge *a, char b, int shift)
{
	int i;
	char temp, p = 0;
	for (i = 0; i < shift; i++)
		*(number + i) = 0;
	for (i = 0; i < a->length; i++)
	{
		temp = a->get_digit(i) * b + p;
		*(number + i + shift) = temp % FOUNDATION;
		p = temp / FOUNDATION;
	}
	*(number + a->length + shift) = p;
	length = a->length + shift + (p != 0);
}

void Huge::init(int b)
{
	if (b == 0)
		length = 0;
	while (b > 0)
	{	
		*(number + length++) = (char)(b % FOUNDATION);
		b /= FOUNDATION;
	}
}

void Huge::print()
{
	int i;
	for(i = 1; i <= length; i++)
		printf("%d", *(number + length - i));
	printf("\n");
}

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	int i, k;
	Huge result, q;
	scanf("%d", &k);
	result.init(36);
	q.init(55);
	for (i = 1; i < k; i++)
		result.mul(&result, &q);
	result.print();
}