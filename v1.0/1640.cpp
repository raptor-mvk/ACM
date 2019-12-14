// телепортироваться можно всегда в одну и ту же точку, например, (1001,0)
// радиус - максимальное среди расстояний до всех демонов

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

class geom_vector
{
private:
  vector<double> coords;
public:
  geom_vector(int n...)
  {
    int *p1=&n;
    double *p2;
    p1++;
    p2=(double*)p1;
    for(int i=0;i<n;i++)
    {
      coords.push_back(*(p2++));
    }
  }

  int size() const
  {
    return coords.size();
  }
  
  double operator[](int i) const
  {
    return coords[i];
  }

  double &operator[](int i)
  {
    return coords[i];
  }

  friend double calc_distance(const geom_vector a,const geom_vector b);
};

double calc_distance(const geom_vector a,const geom_vector b)
{
  double dist=0.0;
  if(a.size()!=b.size())
    return -1.0;
  for(int i=0;i<a.size();i++)
    dist+=(a[i]-b[i])*(a[i]-b[i]);
  return sqrt(dist);
}

const double EPS=0.000000001;
const double CENTER_X=1001.000000000;
const double CENTER_Y=0.000000000;

int main()
{
  int n;
  geom_vector *cur,center(2,CENTER_X,CENTER_Y);
  double cur_x,cur_y,cur_radius;
  cur_radius=0.000000000;
  cin>>n;
  for(int i=0;i<n;i++)
  {
    cin>>cur_x>>cur_y;
    cur=new geom_vector(2,cur_x,cur_y);
    if(calc_distance(*cur,center)-cur_radius>EPS)
      cur_radius=calc_distance(*cur,center);
  }
  cout<<fixed<<setprecision(10)<<CENTER_X<<" "<<CENTER_Y<<" "<<cur_radius;
}