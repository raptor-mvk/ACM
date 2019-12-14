#include <stdio.h>
#include <memory.h>

const char MAX_N=90;
const char MAX_K=5;
const char IP_LENGTH=4;

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
  int n,ip,mask,t,beg,end,cur,way_len=0;
  int *ifaces=new int[MAX_N*MAX_K];
  char *ways=new char[MAX_N*MAX_N];
  char *used=new char[MAX_N];
  char *way=new char[MAX_N];
  int *ifaces_count=new int[MAX_N];
  char c;
  Queue *q=new Queue(MAX_N);
  memset(ways,0,MAX_N*MAX_N*sizeof(char));
  memset(used,-1,MAX_N*sizeof(char));
  scanf("%d",&n);
  for(int i=0;i<n;i++)
  {
    scanf("%d",&ifaces_count[i]);
    for(int j=0;j<ifaces_count[i];j++)
    {
      ip=0;
      for(int k=0;k<IP_LENGTH;k++)
      {
        scanf("%d%c",&t,&c);
        ip<<=8;
        ip+=t;
      }
      mask=0;
      for(int k=0;k<IP_LENGTH;k++)
      {
        scanf("%d%c",&t,&c);
        mask<<=8;
        mask+=t;
      }
      ifaces[i*MAX_K+j]=ip&mask;
    }
  }
  scanf("%d%d",&beg,&end);
  for(int i=0;i<n;i++)
    for(int j=0;j<ifaces_count[i];j++)
      for(int k=i+1;k<n;k++)
        for(int l=0;l<ifaces_count[k];l++)
          if(ifaces[i*MAX_K+j]==ifaces[k*MAX_K+l])
          {
            ways[i*MAX_N+k]=1;
            ways[k*MAX_N+i]=1;
            break;
          }
  used[beg-1]=0;
  q->add(beg-1);
  while(!q->is_empty())
  {
    cur=q->get();
    for(int i=0;i<n;i++)
      if(ways[cur*MAX_N+i]&&used[i]==-1)
      {
        used[i]=cur+1;
        q->add(i);
      }
  }
  if(used[end-1]==-1)
    printf("No");
  else
  {
    printf("Yes\n");
    cur=end;
    while(cur!=beg)
    {
      way[way_len++]=cur;
      cur=used[cur-1];
    }
    way[way_len++]=beg;
    for(int i=way_len-1;i>=0;i--)
      printf("%d ",way[i]);
  }
}