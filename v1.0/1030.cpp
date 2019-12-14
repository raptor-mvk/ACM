// переводим угловые координаты в метрические:
//   x=R*cos(a)*cos(b)
//   y=R*cos(a)*sin(b)
//   z=R*sin(a)
// расстояние между двумя точками на сфере равно длине дуги:
//   S=R*a
// чтобы найти угол, используем скалярное произведение:
//   a=acos((s_x*i_x+s_y*i_y+s_z*y_z)/R^2)

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

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

const int MAX_LINE_LENGTH=40;
const double DANGER_DISTANCE=100.00;
const double PI=acos(-1.0);
const double EARTH_RADIUS=3437.5;

double dms2rad(int degrees,int minutes,int seconds)
{
  return ((double)degrees+(double)minutes/60.0+(double)seconds/3600.0)*PI/180;
}

int main()
{
  int x1,x2,x3;
  char xc;
  geom_vector ship,iceberg;
  double distance;
  cin.ignore(MAX_LINE_LENGTH,'\n');
  cin.ignore(MAX_LINE_LENGTH,'\n');
  cin.ignore(MAX_LINE_LENGTH,'\n');
  cin>>x1;
  cin.ignore(1);
  cin>>x2;
  cin.ignore(1);
  cin>>x3;
  ship.push_back(dms2rad(x1,x2,x3));
  cin.ignore(2);
  cin>>xc;
  if(xc=='N')
    ship[0]=-ship[0];
  cin.ignore(MAX_LINE_LENGTH,'\n');
  cin.ignore(4);
  cin>>x1;
  cin.ignore(1);
  cin>>x2;
  cin.ignore(1);
  cin>>x3;
  ship.push_back(dms2rad(x1,x2,x3));
  cin.ignore(2);
  cin>>xc;
  if(xc=='W')
    ship[1]=-ship[1];
  ship.push_back(EARTH_RADIUS);
  cin.ignore(MAX_LINE_LENGTH,'\n');
  cin.ignore(MAX_LINE_LENGTH,'\n');
  cin>>x1;
  cin.ignore(1);
  cin>>x2;
  cin.ignore(1);
  cin>>x3;
  iceberg.push_back(dms2rad(x1,x2,x3));
  cin.ignore(2);
  cin>>xc;
  if(xc=='N')
    iceberg[0]=-iceberg[0];
  cin.ignore(MAX_LINE_LENGTH,'\n');
  cin.ignore(4);
  cin>>x1;
  cin.ignore(1);
  cin>>x2;
  cin.ignore(1);
  cin>>x3;
  iceberg.push_back(dms2rad(x1,x2,x3));
  cin.ignore(2);
  cin>>xc;
  if(xc=='W')
    iceberg[1]=-iceberg[1];
  iceberg.push_back(EARTH_RADIUS);
  ship.sph2dec();
  iceberg.sph2dec();
  distance=EARTH_RADIUS*get_angle(ship,iceberg);
  cout<<"The distance to the iceberg: "<<fixed<<setprecision(2)<<distance;
  cout<<" miles.";
  if(DANGER_DISTANCE-distance>0.005)
    cout<<endl<<"DANGER!";
}