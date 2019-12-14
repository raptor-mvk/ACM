// генерируем случайную последовательность, на каждом шаге проверяя выполнение
// заданных условий

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

template <class T> class array_2d
{
private:
  vector<T> *data;
  int dim[2];
public:
  array_2d()
  {
    dim[0]=0;
    dim[1]=0;
    data=NULL;
  }

  array_2d(int n,int m,T value=(T)0)
  {
    dim[0]=n;
    dim[1]=m;
    data=new vector<T>[n];
    for(int i=0;i<n;i++)
      data[i].assign(m,value);
  }

  array_2d(array_2d &a)
  {
    dim[0]=a.dim[0];
    dim[1]=a.dim[1];
    data=new vector<T>[dim[0]];
    for(int i=0;i<dim[0];i++)
      data[i]=a.data[i];
  }

  ~array_2d()
  {
    delete[]data;
  }

  void assign(int n,int m,T value=(T)0)
  {
    delete[]data;
    dim[0]=n;
    dim[1]=m;
    data=new vector<T>[n];
    for(int i=0;i<n;i++)
      data[i].assign(m,value);
  }

  vector<T> &operator[](int i) const
  {
    return data[i];
  }

  vector<T> &operator[](int i)
  {
    return data[i];
  }

  array_2d &operator=(const array_2d &a)
  {
    delete[]data;
    dim[0]=a.dim[0];
    dim[1]=a.dim[1];
    data=new vector<T>[dim[0]];
    for(int i=0;i<dim[0];i++)
      data[i]=a.data[i];
  }
};

template <class T> class array_3d
{
private:
  array_2d<T> *data;
  int dim[3];
public:
  array_3d()
  {
    dim[0]=0;
    dim[1]=0;
    dim[2]=0;
    data=NULL;
  }

  array_3d(int n,int m,int k,T value=(T)0)
  {
    dim[0]=n;
    dim[1]=m;
    dim[2]=k;
    data=new array_2d<T>[n];
    for(int i=0;i<n;i++)
      data[i].assign(m,k,value);
  }

  array_3d(array_3d &a)
  {
    dim[0]=a.dim[0];
    dim[1]=a.dim[1];
    dim[2]=a.dim[2];
    data=new array_2d<T>[dim[0]];
    for(int i=0;i<dim[0];i++)
      data[i]=a.data[i];
  }

  void assign(int n,int m,int k,T value=(T)0)
  {
    delete[]data;
    dim[0]=n;
    dim[1]=m;
    dim[2]=k;
    data=new array_2d<T>[n];
    for(int i=0;i<n;i++)
      data[i].assign(m,k,value);
  }

  array_2d<T> &operator[](int i) const
  {
    return data[i];
  }

  array_2d<T> &operator[](int i)
  {
    return data[i];
  }
};

const int SINGLE_SIZE=26;
const int NUMBER=1000000;
const int MAX_TRIPLE=100;
const int MAX_DOUBLE=2000;
const int MAX_SINGLE=40000;

int main()
{
  vector<int> singles;
  array_2d<int> doubles;
  array_3d<int> triples;
  char cur,prev,prevv;
  string str;
  singles.assign(SINGLE_SIZE,0);
  doubles.assign(SINGLE_SIZE,SINGLE_SIZE,0);
  triples.assign(SINGLE_SIZE,SINGLE_SIZE,SINGLE_SIZE,0);
  prevv=rand()%SINGLE_SIZE;
  str+=prevv+'a';
  singles[(int)prevv]++;
  prev=rand()%SINGLE_SIZE;
  str+=prev+'a';
  singles[(int)prev]++;
  doubles[(int)prevv][(int)prev]++;
  for(int i=2;i<NUMBER;i++)
  {
    cur=rand()%SINGLE_SIZE;
    if (++singles[(int)cur]>MAX_SINGLE)
    {
      --i;
      --singles[(int)cur];
    }
    else
    {
      if (++doubles[(int)prev][(int)cur]>MAX_DOUBLE)
      {
        --i;
        --singles[(int)cur];
        --doubles[(int)prev][(int)cur];
      }
      else
      {
        if (++triples[(int)prevv][(int)prev][(int)cur]>MAX_TRIPLE)
          {
            --i;
            --singles[(int)cur];
            --doubles[(int)prev][(int)cur];
            --triples[(int)prevv][(int)prev][(int)cur];
          }
        str+=cur+'a';
      }
    }
    prevv=prev;
    prev=cur;
  }
  cout<<str;
}