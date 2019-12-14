#include <stdio.h>
#include <memory.h>

const int MAX_N = 100;
const int HUGE_LENGTH = 180;
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
  int get_length();
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

int Huge::get_length()
{
  return length;
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
  if (b == 0)
  {
    this->init(0);
    return;
  }
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
  {
    length = 1;
    *number = 0;
  }
  else length = 0;
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
  int *perm=new int[MAX_N];
  int *pos=new int[MAX_N];
  Huge count;
  Huge temp;
  Huge facts[MAX_N];
  int n,cur;
  scanf("%d",&n);
  for(int i=0;i<n;i++)
    scanf("%d",&perm[i]);
  for(int i=n-1;i>0;i--)
  {
    cur=1;
    for(int j=n-1;j>0;j--)
      if(perm[j]<i+1) cur++;
      else if(perm[j]==i+1) break;
    pos[i]=cur;
  }
  facts[n-1].init(1);
  for(int i=n-2;i>0;i--)
  {
    count.init(i+2);
    facts[i].mul(&facts[i+1],&count);
  }
  count.init(1);
  temp.init(pos[1]-1);
  temp.mul(&facts[1],&temp);
  count.sum(&count,&temp);
  cur=1-pos[1]%2;
  for(int i=2;i<n;i++)
  {
    if(cur)
    {
      temp.init(i+1-pos[i]);
      cur=1-(i-pos[i]+cur*(i+1))%2;
    }
    else
    {
      temp.init(pos[i]-1);
      cur=1-(pos[i]+cur*(i+1))%2;
    }
    temp.mul(&facts[i],&temp);
    count.sum(&count,&temp);
  }
  count.print();
}
