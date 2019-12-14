// геометрические функции: арккосинус, вычисление длины вектора, вычисление
// угла между векторами

const double PI = acos(-1.0);
const int N = 3;

double acos1(double angle)
{
  if (angle > 1.0)
    return 0;
  if (angle < -1.0)
    return PI;
  return acos(angle);
}

double get_length(int *vect)
{
  int i;
  double length = 0.0;
  for (i = 0; i < N; i++)
    length += (double)*(vect + i) * (double)*(vect + i);
  return sqrt(length);
}

double get_angle(int *first, int *second)
{
  int i;
  double angle = 0.0;
  for (i = 0; i < N; i++)
    angle += (double)*(first + i) * (double)*(second + i);
  return acos1(angle / get_length(first) / get_length(second));
}
