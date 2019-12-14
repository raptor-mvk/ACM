// вершина графа - (позици€ на доске, положение кубика)
// запускаетс€ волна по графу
// положение кубика описываетс€ шестЄркой (ближн€€, дальн€€, лева€, права€,
// верхн€€, нижн€€)

#include <iostream>
#include <queue>

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
    data[0].assign(m,0);
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

  int size()
  {
    return dim[0]*dim[1];
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

  int size()
  {
    return dim[0]*dim[1]*dim[2];
  }
};

class permutation
{
protected:
  vector<int> position;
  long long count;
public:
  permutation()
  {    
  }

  permutation(int n...)
  {
    int *p1=&n;
    count=1;
    for(int i=0;i<n;)
    {
      position.push_back(*(++p1));
      count*=++i;
    }
  }

  int operator[](int i) const
  {
    return position[i];
  }

  int &operator[](int i)
  {
    return position[i];
  }

  permutation &operator=(const permutation &a)
  {
    position=a.position;
    count=a.count;
    return *this;
  }

  int size() const
  {
    return position.size();
  }

  int number()
  {
    vector<char> used;
    int num=0,count;
    used.assign(size(),0);
    for(int i=0;i<size()-1;i++)
    {
      count=-1;
      for(int j=0;j<=position[i];j++)
        if(!used[j])
          count++;
      num+=count;
      used[position[i]]=1;
      num*=size()-1-i;
    }
    return num;
  }

  void set(int num)
  {
    vector<char> used;
    int cur_div=count/size();
    int j,count;
    used.assign(size(),0);
    for(int i=0;i<size()-1;i++)
    {
      count=num/cur_div;
      j=0;
      while(count>-1)
        if(!used[j++])
          count--;
      used[--j]=1;
      position[i]=j;
      num=num%cur_div;
      cur_div=cur_div/(size()-1-i);
    }
    j=0;
    while (used[j++]);
    position[size()-1]=--j;
  }

  long long get_count()
  {
    return count;
  }

  void rotate_right()
  {
    int temp;
    temp=position[2];
    position[2]=position[5];
    position[5]=position[3];
    position[3]=position[4];
    position[4]=temp;
  }

  void rotate_left()
  {
    int temp;
    temp=position[2];
    position[2]=position[4];
    position[4]=position[3];
    position[3]=position[5];
    position[5]=temp;
  }

  void rotate_forward()
  {
    int temp;
    temp=position[0];
    position[0]=position[4];
    position[4]=position[1];
    position[1]=position[5];
    position[5]=temp;
  }

  void rotate_backward()
  {
    int temp;
    temp=position[0];
    position[0]=position[5];
    position[5]=position[1];
    position[1]=position[4];
    position[4]=temp;
  }
};

const int TABLE_HEIGHT=8;
const int TABLE_WIDTH=8;
const int SIDES_COUNT=6;
const int BOTTOM_SIDE=5;
const char NO_MOVE=-1;
const char MOVE_RIGHT=0;
const char MOVE_LEFT=1;
const char MOVE_FORWARD=2;
const char MOVE_BACKWARD=3;

int main()
{
  permutation cur_pos(SIDES_COUNT,0,1,5,3,2,4);
  permutation new_pos(cur_pos);
  int cube[SIDES_COUNT];
  array_3d<int> table;
  array_3d<char> prev_move;
  queue<int> pos_x,pos_y,pos_z;
  char beg_pos_x,beg_pos_y,end_pos_x,end_pos_y;
  int min_id,min=1000000000;
  vector<char> way_x,way_y;
  table.assign(TABLE_HEIGHT,TABLE_WIDTH,cur_pos.get_count(),-1);
  prev_move.assign(TABLE_HEIGHT,TABLE_WIDTH,cur_pos.get_count(),NO_MOVE);
  cin>>beg_pos_x>>beg_pos_y;
  beg_pos_x-='a';
  beg_pos_y-='1';
  cin.ignore(1);
  cin>>end_pos_x>>end_pos_y;
  end_pos_x-='a';
  end_pos_y-='1';
  for(int i=0;i<SIDES_COUNT;i++)
    cin>>cube[i];
  pos_x.push((int)beg_pos_x);
  pos_y.push((int)beg_pos_y);
  pos_z.push(cur_pos.number());
  table[pos_x.front()][pos_y.front()][pos_z.front()]=
    cube[cur_pos[BOTTOM_SIDE]];
  while(!pos_x.empty())
  {
    cur_pos.set(pos_z.front());
    if(pos_x.front()<TABLE_WIDTH-1)
    {
      new_pos=cur_pos;
      new_pos.rotate_right();
      if((table[pos_x.front()+1][pos_y.front()][new_pos.number()]==-1)||
        (table[pos_x.front()+1][pos_y.front()][new_pos.number()]>
        table[pos_x.front()][pos_y.front()][cur_pos.number()]+
        cube[new_pos[BOTTOM_SIDE]]))
        {
          table[pos_x.front()+1][pos_y.front()][new_pos.number()]=
            table[pos_x.front()][pos_y.front()][cur_pos.number()]+
            cube[new_pos[BOTTOM_SIDE]];
          prev_move[pos_x.front()+1][pos_y.front()][new_pos.number()]=
            MOVE_RIGHT;
          pos_x.push(pos_x.front()+1);
          pos_y.push(pos_y.front());
          pos_z.push(new_pos.number());
        }
    }
    if(pos_x.front()>0)
    {
      new_pos=cur_pos;
      new_pos.rotate_left();
      if((table[pos_x.front()-1][pos_y.front()][new_pos.number()]==-1)||
        (table[pos_x.front()-1][pos_y.front()][new_pos.number()]>
        table[pos_x.front()][pos_y.front()][cur_pos.number()]+
        cube[new_pos[BOTTOM_SIDE]]))
        {
          table[pos_x.front()-1][pos_y.front()][new_pos.number()]=
            table[pos_x.front()][pos_y.front()][cur_pos.number()]+
            cube[new_pos[BOTTOM_SIDE]];
          prev_move[pos_x.front()-1][pos_y.front()][new_pos.number()]=
            MOVE_LEFT;
          pos_x.push(pos_x.front()-1);
          pos_y.push(pos_y.front());
          pos_z.push(new_pos.number());
        }
    }
    if(pos_y.front()<TABLE_HEIGHT-1)
    {
      new_pos=cur_pos;
      new_pos.rotate_backward();
      if((table[pos_x.front()][pos_y.front()+1][new_pos.number()]==-1)||
        (table[pos_x.front()][pos_y.front()+1][new_pos.number()]>
        table[pos_x.front()][pos_y.front()][cur_pos.number()]+
        cube[new_pos[BOTTOM_SIDE]]))
        {
          table[pos_x.front()][pos_y.front()+1][new_pos.number()]=
            table[pos_x.front()][pos_y.front()][cur_pos.number()]+
            cube[new_pos[BOTTOM_SIDE]];
          prev_move[pos_x.front()][pos_y.front()+1][new_pos.number()]=
            MOVE_BACKWARD;
          pos_x.push(pos_x.front());
          pos_y.push(pos_y.front()+1);
          pos_z.push(new_pos.number());
        }
    }
    if(pos_y.front()>0)
    {
      new_pos=cur_pos;
      new_pos.rotate_forward();
      if((table[pos_x.front()][pos_y.front()-1][new_pos.number()]==-1)||
        (table[pos_x.front()][pos_y.front()-1][new_pos.number()]>
        table[pos_x.front()][pos_y.front()][cur_pos.number()]+
        cube[new_pos[BOTTOM_SIDE]]))
        {
          table[pos_x.front()][pos_y.front()-1][new_pos.number()]=
            table[pos_x.front()][pos_y.front()][cur_pos.number()]+
            cube[new_pos[BOTTOM_SIDE]];
          prev_move[pos_x.front()][pos_y.front()-1][new_pos.number()]=
            MOVE_FORWARD;
          pos_x.push(pos_x.front());
          pos_y.push(pos_y.front()-1);
          pos_z.push(new_pos.number());
        }
    }
    pos_x.pop();
    pos_y.pop();
    pos_z.pop();
  }
  for(int i=0;i<cur_pos.get_count();i++)
  {
    if((table[(int)end_pos_x][(int)end_pos_y][i]>-1)&&
      (table[(int)end_pos_x][(int)end_pos_y][i]<min))
      {
        min_id=i;
        min=table[(int)end_pos_x][(int)end_pos_y][i];
      }
  }
  cout<<min;
  cur_pos.set(min_id);
  way_x.push_back((char)(end_pos_x+'a'));
  way_y.push_back((char)(end_pos_y+'1'));
  while(prev_move[(int)end_pos_x][(int)end_pos_y][cur_pos.number()]!=NO_MOVE)
  {
    if(prev_move[(int)end_pos_x][(int)end_pos_y][cur_pos.number()]==MOVE_RIGHT)
    {
      cur_pos.rotate_left();
      end_pos_x--;
    }
    else
      if(prev_move[(int)end_pos_x][(int)end_pos_y][cur_pos.number()]==
        MOVE_LEFT)
        {
          cur_pos.rotate_right();
          end_pos_x++;
        }
      else
        if(prev_move[(int)end_pos_x][(int)end_pos_y][cur_pos.number()]==
          MOVE_FORWARD)
          {
            cur_pos.rotate_backward();
            end_pos_y++;
          }
        else
          if(prev_move[(int)end_pos_x][(int)end_pos_y][cur_pos.number()]==
            MOVE_BACKWARD)
            {
              cur_pos.rotate_forward();
              end_pos_y--;
            }
    way_x.push_back((char)(end_pos_x+'a'));
    way_y.push_back((char)(end_pos_y+'1'));
  }
  for(int i=way_x.size()-1;i>=0;i--)
    cout<<" "<<way_x[i]<<way_y[i];
}