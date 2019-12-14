#include <vector>

using namespace std;

class permutation
{
private:
  vector<int> position;
  long long count;
public:
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
};