#include <stdio.h>
#include <memory.h>

const int MAX_N=30000;
const int T_DELETE=600;

class Heap
{
private:
  int *heap_keys;
  int *heap_data;
  int cur_size;
  void heapify(int id);
  void apply_get();
public:
  Heap(int new_size);
  ~Heap();
  bool is_empty();
  void add(int new_key,int new_data);
  int get_key(char apply);
  int get_data(char apply);
};

Heap::Heap(int new_size)
{
  heap_keys=new int[new_size];
  heap_data=new int[new_size];
  cur_size=0;
}

Heap::~Heap()
{
  delete [] heap_keys;
  delete [] heap_data;
}

bool Heap::is_empty()
{
  return cur_size==0;
}

void Heap::add(int new_key,int new_data)
{
  int temp,id=cur_size;
  heap_keys[cur_size]=new_key;
  heap_data[cur_size++]=new_data;
  while(1)
  {
    if((id>0)&&(heap_keys[id]<heap_keys[id>>1]))
    {
      temp=heap_keys[id];
      heap_keys[id]=heap_keys[id>>1];
      heap_keys[id>>1]=temp;
      temp=heap_data[id];
      heap_data[id]=heap_data[id>>1];
      heap_data[id>>1]=temp;
      id>>=1;
    }
    else break;
  }
}

int Heap::get_key(char apply)
{
  int key=heap_keys[0];
  if(apply) apply_get();
  return key;
}

int Heap::get_data(char apply)
{
  int data=heap_data[0];
  if(apply) apply_get();
  return data;
}

void Heap::apply_get()
{
  heap_keys[0]=heap_keys[--cur_size];
  heap_data[0]=heap_data[cur_size];
  heapify(0);
}

void Heap::heapify(int id)
{
  int temp;
  int min_id;
  while(1)
  {
    min_id=id;
    if ((2*id+1<cur_size)&&(heap_keys[2*id+1]<heap_keys[min_id]))
      min_id=2*id+1;
    if ((2*id<cur_size)&&(heap_keys[2*id]<heap_keys[min_id]))
      min_id=2*id;
    if(min_id!=id)
    {
      temp=heap_keys[id];
      heap_keys[id]=heap_keys[min_id];
      heap_keys[min_id]=temp;
      temp=heap_data[id];
      heap_data[id]=heap_data[min_id];
      heap_data[min_id]=temp;
      id=min_id;
    }
    else break;
  }
}

int main()
{
  int first=0,t,n,cur;
  int *allocated=new int[MAX_N];
  char c;
  Heap *free_blocks=new Heap(MAX_N);
  Heap *busy_blocks=new Heap(MAX_N);
  memset(allocated,0,MAX_N*sizeof(int));
  while(scanf("%d %c",&t,&c)!=EOF)
  {
    while(!busy_blocks->is_empty())
    {
      cur=busy_blocks->get_key(0);
      if(cur<=t)
      {
        cur=busy_blocks->get_data(1);
        if(allocated[cur]>t)
          busy_blocks->add(allocated[cur],cur);
        else
        {
          free_blocks->add(cur,0);
          allocated[cur]=0;
        }
      }
      else break;
    }
    if(c=='+')
    {
      if(!free_blocks->is_empty())
        cur=free_blocks->get_key(1);
      else
        cur=first++;
      busy_blocks->add(t+T_DELETE,cur);
      allocated[cur]=t+T_DELETE;
      printf("%d\n",cur+1);
    }
    else
    {
      scanf("%d",&n);
      if(allocated[n-1])
      {
        allocated[n-1]=t+T_DELETE;
        printf("+\n");
      }
      else printf("-\n");
    }
  }
}