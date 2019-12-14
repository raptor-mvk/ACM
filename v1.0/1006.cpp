// перебираются все возможные положения окон, для каждого положения
// проверяется, могло ли оно быть выведено в данный момент
// если да, то окно заносится в стек и пиксели помечаются как отрисованные

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const unsigned char LTF=218;
const unsigned char RTF=191;
const unsigned char LBF=192;
const unsigned char RBF=217;
const unsigned char VF=179;
const unsigned char HF=196;
const unsigned char EMPTY=46;
const unsigned char ANY=200;
const int DESKTOP_WIDTH=50;
const int DESKTOP_HEIGHT=20;
const int DESKTOP_SIZE=DESKTOP_HEIGHT*DESKTOP_WIDTH;

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

bool check_frame(const array_2d<unsigned char> desktop,int x,int y,int size)
{
  bool not_covered=false;
  if((desktop[y][x]!=LTF)&&(desktop[y][x]!=ANY))
    return false;
  if(desktop[y][x]==LTF)
    not_covered=true;
  if((desktop[y+size-1][x]!=LBF)&&(desktop[y+size-1][x]!=ANY))
    return false;
  if(desktop[y+size-1][x]==LBF)
    not_covered=true;
  if((desktop[y][x+size-1]!=RTF)&&(desktop[y][x+size-1]!=ANY))
    return false;
  if(desktop[y][x+size-1]==RTF)
    not_covered=true;
  if((desktop[y+size-1][x+size-1]!=RBF)&&(desktop[y+size-1][x+size-1]!=ANY))
    return false;
  if(desktop[y+size-1][x+size-1]==RBF)
    not_covered=true;
  if(size>2)
    for(int i=1;i<size-1;i++)
    {
      if((desktop[y][x+i]!=HF)&&(desktop[y][x+i]!=ANY))
        return false;
      if(desktop[y][x+i]==HF)
        not_covered=true;
      if((desktop[y+size-1][x+i]!=HF)&&(desktop[y+size-1][x+i]!=ANY))
        return false;
      if(desktop[y+size-1][x+i]==HF)
        not_covered=true;
      if((desktop[y+i][x]!=VF)&&(desktop[y+i][x]!=ANY))
        return false;
      if(desktop[y+i][x]==VF)
        not_covered=true;
      if((desktop[y+i][x+size-1]!=VF)&&(desktop[y+i][x+size-1]!=ANY))
        return false;
      if(desktop[y+i][x+size-1]==VF)
        not_covered=true;
    }
  return not_covered;
}

int mark_frame(array_2d<unsigned char> *desktop,int x,int y,int size)
{
  int marked=0;
  if((*desktop)[y][x]!=ANY)
    marked++;
  (*desktop)[y][x]=ANY;
  if((*desktop)[y+size-1][x]!=ANY)
    marked++;
  (*desktop)[y+size-1][x]=ANY;
  if((*desktop)[y][x+size-1]!=ANY)
    marked++;
  (*desktop)[y][x+size-1]=ANY;
  if((*desktop)[y+size-1][x+size-1]!=ANY)
    marked++;
  (*desktop)[y+size-1][x+size-1]=ANY;
  for(int i=1;i<size-1;i++)
  {
    if((*desktop)[y][x+i]!=ANY)
      marked++;
    (*desktop)[y][x+i]=ANY;
    if((*desktop)[y+size-1][x+i]!=ANY)
      marked++;
    (*desktop)[y+size-1][x+i]=ANY;
    if((*desktop)[y+i][x]!=ANY)
      marked++;
    (*desktop)[y+i][x]=ANY;
    if((*desktop)[y+i][x+size-1]!=ANY)
      marked++;
    (*desktop)[y+i][x+size-1]=ANY;
  }
  return marked;
}

int main()
{
  array_2d<unsigned char> desktop(DESKTOP_HEIGHT,DESKTOP_WIDTH);
  int points_count=0,max_size;
  stack<int> st;
  int cur_frame,frames_count=0;
  for(int i=0;i<DESKTOP_HEIGHT;i++)
  {
     for(int j=0;j<DESKTOP_WIDTH;j++)
     {
       cin>>desktop[i][j];
       if(desktop[i][j]!=EMPTY)
         points_count++;
     }
  }
  while(points_count>0)
    for(int i=0;i<DESKTOP_HEIGHT-1;i++)
      for(int j=0;j<DESKTOP_WIDTH-1;j++)
      {
        max_size=(DESKTOP_HEIGHT-i>DESKTOP_WIDTH-j)?
          (DESKTOP_WIDTH-j):(DESKTOP_HEIGHT-i);
        for(int k=2;k<=max_size;k++)
          if(desktop[i][j]!=EMPTY)
            if(check_frame(desktop,j,i,k))
            {
              st.push(k*DESKTOP_SIZE+i*DESKTOP_WIDTH+j);
              points_count-=mark_frame(&desktop,j,i,k);
              frames_count++;
            }
      }
  cout<<frames_count<<endl;
  while(!st.empty())
  {
    cur_frame=st.top();
    st.pop();
    cout<<cur_frame%DESKTOP_WIDTH<<" "<<(cur_frame%DESKTOP_SIZE)/DESKTOP_WIDTH;
    cout<<" "<<cur_frame/DESKTOP_SIZE<<endl;
  }
}