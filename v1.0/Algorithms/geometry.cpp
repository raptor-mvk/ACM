#include <cmath>
#include <vector>

using namespace std;

class geom_vector
{
private:
  vector<double> coords;
public:
  geom_vector()
  {
  }

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

  double operator*(const geom_vector &a) const
  {
    double res=0.0;
    if(a.size()!=size())
      return 1e308;
    for(int i=0;i<a.size();i++)
      res+=a[i]*coords[i];
    return res;    
  }

  double length() const
  {
    double res=0.0;
    for(int i=0;i<size();i++)
      res+=coords[i]*coords[i];
    return sqrt(res);    
  }

  void push_back(double a)
  {
    coords.push_back(a);
  }

  void sph2dec()
  {
    if(coords.size()==3)
    {
      vector<double> temp;
      temp.push_back(coords[2]*cos(coords[0])*cos(coords[1]));
      temp.push_back(coords[2]*cos(coords[0])*sin(coords[1]));
      temp.push_back(coords[2]*sin(coords[0]));
      coords=temp;
    }
  }

  friend double calc_distance(const geom_vector a,const geom_vector b);
  friend double get_angle(const geom_vector a,const geom_vector b);
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

double get_angle(const geom_vector a,const geom_vector b)
{
  if(a.size()!=b.size())
    return 1e308;
  return acos((a*b)/a.length()/b.length());
}
