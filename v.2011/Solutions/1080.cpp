// по графу запускается "волна", которая красит текущую вершину в цвет,
// отличный от предыдущей
// если текущая вершина уже раскрашена, то проверяется отличие цвета от
// предыдущей вершины, иначе выводится -1

#include <iostream>
#include <queue>
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

int main()
{
  int n,cur;
  char found=1;
  vector<char> colors;
  array_2d<char> adj;
  queue<int> q;
  cin>>n;
  adj.assign(n,n,0);
  colors.assign(n,(char)(-1));
  for(int i=0;i<n;i++)
  {
    cin>>cur;
    while(cur>0)
    {
      adj[i][cur-1]=1;
      adj[cur-1][i]=1;
      cin>>cur;
    }
  }
  colors[0]=0;
  q.push(0);
  while(!q.empty())
  {
    cur=q.front();
    q.pop();
    for(int i=0;i<n;i++)
      if(adj[cur][i])
      {
        if(colors[i]==-1)
        {
          q.push(i);
          colors[i]=colors[cur]^1;
        }
        else
          if(colors[i]==colors[cur])
            found=0;
      }
  }
  if(found)
    for(int i=0;i<n;i++)
      cout<<(char)(colors[i]+'0');
  else
    cout<<"-1";
}
